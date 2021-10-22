// Functions to allocate memory and manipulate its protection on Windows
//
// Copyright 2021 MobSlicer152
// This file is part of Shard C Library 2
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "stdlib.h"
#include "string.h"

#include "internal/crt0.h"
#include "internal/win32/defs.h"
#include "internal/win32/ldr.h"

_LIBC_DLLSYM void *__alloc(size_t *size)
{
	uint32_t status;
	size_t orig_size = *size;
	uint8_t *ret = NULL;
	size_t free_mem;

	// Check if there's even enough free memory (doesn't work on Windows 7)
	free_mem = __get_free_mem();
	if (orig_size > free_mem)
		return NULL;

	// Request the memory
	status = __NtAllocateVirtualMemory(-1, &ret, 0, size,
					   MEM_COMMIT | MEM_RESERVE,
					   PAGE_READWRITE);
	if (status != 0 || !ret || *size < orig_size)
		return NULL;

	// The spec for NtAllocateVirtualMemory guarantees the pages to be zeroed.
	return ret;
}

_LIBC_DLLSYM size_t __get_free_mem(void)
{
	SYSTEM_BASIC_INFORMATION sys_info;
	VM_COUNTERS mem_usage;
	size_t mem_total;
	size_t mem_free;

	// Get system information
	__NtQuerySystemInformation(SystemBasicInformation, &sys_info,
				   sizeof(SYSTEM_BASIC_INFORMATION), NULL);

	// Calculate total memory
	mem_total = (sys_info.MaximumUserModeAddress -
		     sys_info.MinimumUserModeAddress) +
		    1;

	// Query memory in use
	__NtQueryInformationProcess(-1, ProcessVmCounters, &mem_usage,
				    sizeof(VM_COUNTERS), NULL);

	// Calculate free memory
	mem_free = mem_total - mem_usage.VirtualSize;
	return mem_free;
}

_LIBC_DLLSYM void __free(void *chunk, size_t size)
{
	// Free the memory
	__NtFreeVirtualMemory(-1, &chunk, &size, MEM_RELEASE);
}
