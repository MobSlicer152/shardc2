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

void *__alloc(size_t size)
{
	uint32_t status;
	uint8_t *ret = NULL;
	size_t real_size = size + sizeof(struct __basic_alloc_info);
	struct __basic_alloc_info *info;

	// Check if there's even enough free memory (doesn't work on Windows 7)
	//if (real_size > __get_free_mem())
	//	return NULL;

	// Request the memory
	status = __NtAllocateVirtualMemory(-1, &ret, 0, &real_size, MEM_COMMIT | MEM_RESERVE,
				  PAGE_READWRITE);
	if (status != 0 || !ret || real_size < size)
		return NULL;

	// Store information for freeing this allocation
	info = (struct __basic_alloc_info *)ret;
	info->magic = _BASIC_ALLOC_MAGIC;
	info->size = real_size;

	// Zero the rest of the memory, to prevent garbage from leaking in
	ret += sizeof(struct __basic_alloc_info);
	memset(ret, 0, real_size - sizeof(struct __basic_alloc_info));

	return ret;
}

size_t __get_free_mem(void)
{
	SYSTEM_BASIC_INFORMATION sys_info;
	VM_COUNTERS mem_usage;
	size_t mem_total;

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

	return mem_total - mem_usage.VirtualSize;
}

void __free(void *chunk)
{
	struct __basic_alloc_info *info =
		(struct __basic_alloc_info *)((uint8_t *)chunk -
					      sizeof(struct __basic_alloc_info));
	size_t size;

	// Check the pointer
	if (!(info->magic == _BASIC_ALLOC_MAGIC || info->magic == _ALLOC_MAGIC))
		return;

	// Free the memory
	size = info->size;
	__NtFreeVirtualMemory(-1, &info, &size, MEM_RELEASE);
}
