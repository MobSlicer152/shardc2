// Windows utility functions
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

#include "internal/win32/defs.h"
#include "internal/win32/ldr.h"

uint8_t *__get_parent_base(void)
{
	PROCESS_BASIC_INFORMATION info;
	OBJECT_ATTRIBUTES attrs = { 0 };
	uintptr_t parent;
	CLIENT_ID client_id;
	uint8_t *base;

	// Query process info
	__NtQueryInformationProcess(-1, ProcessBasicInformation, &info,
				    sizeof(PROCESS_BASIC_INFORMATION), NULL);

	// Open the process
	InitializeObjectAttributes(&attrs, NULL,
				   OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
				   NULL, NULL);
	__NtOpenProcess(&parent, PROCESS_QUERY_INFORMATION, &attrs, &client_id);

	// Get the parent's information
	__NtQueryInformationProcess(parent, ProcessBasicInformation, &info,
				    sizeof(PROCESS_BASIC_INFORMATION), NULL);

	// Get the base address through NTDLL
	__LdrLoadDll(NULL, NULL,
		     &info.PebBaseAddress->ProcessParameters->ImagePathName,
		     &base);

	// Return the address
	return base;
}

uint16_t __get_image_subsystem(uint8_t *base)
{
	IMAGE_DOS_HEADER *dos_hdr = (IMAGE_DOS_HEADER *)base;
	IMAGE_NT_HEADERS *nt_hdrs;

	nt_hdrs = (IMAGE_NT_HEADERS *)(base + dos_hdr->e_lfanew);
	return nt_hdrs->OptionalHeader.Subsystem;
}
