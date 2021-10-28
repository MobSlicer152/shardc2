// Interface for the Windows dynamic linker, and a function to
// load functions the library makes use of
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

#include "internal/win32/ldr.h"

// Base addresses of important DLLs
_LIBC_DLLSYM uint8_t *__ntdll;
_LIBC_DLLSYM uint8_t *__kernel32;

// Function pointers
_LIBC_DLLSYM long (*__LdrGetProcedureAddress)(void *base, ANSI_STRING *name,
					      unsigned long ord,
					      void **func_out) = 0;
_LIBC_DLLSYM long (*__LdrLoadDll)(wchar_t *path, unsigned long *characteristics,
				  UNICODE_STRING *name, void **base_out) = 0;
_LIBC_DLLSYM long (*__LdrUnloadDll)(void *base) = 0;

_LIBC_DLLSYM long (*__NtAllocateVirtualMemory)(
	uintptr_t process, void *preferred_base, uintptr_t address_bitmask,
	size_t *size, uint32_t alloc_type, uint32_t prot) = 0;
_LIBC_DLLSYM long (*__NtCloseHandle)(uintptr_t handle) = 0;
_LIBC_DLLSYM long (*__NtFreeVirtualMemory)(uintptr_t process, void **base,
					   size_t *size, uint32_t type) = 0;
_LIBC_DLLSYM long (*__NtOpenProcess)(uintptr_t *handle_out, uint32_t access,
				     OBJECT_ATTRIBUTES *attrs,
				     CLIENT_ID *client_id) = 0;
_LIBC_DLLSYM long (*__NtProtectVirtualMemory)(uintptr_t process, void *base,
					      size_t *size, uint32_t prot,
					      uint32_t *old_prot) = 0;
_LIBC_DLLSYM long (*__NtQueryInformationProcess)(uintptr_t process,
						 PROCESSINFOCLASS info_type,
						 void *info,
						 uint32_t info_buffer_size,
						 uint32_t *info_size) = 0;
_LIBC_DLLSYM long (*__NtQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS info_type, void *info,
	uint32_t info_buffer_size, uint32_t *info_size) = 0;
_LIBC_DLLSYM long (*__NtTerminateProcess)(uintptr_t handle,
					  uint32_t status) = 0;

_LIBC_DLLSYM void __load_lib_dep_funcs(PEB *peb)
{
	PEB_LDR_DATA *ldr;
	LIST_ENTRY *head;
	LIST_ENTRY *cur;
	LDR_DATA_TABLE_ENTRY *cur_dll;
	IMAGE_DOS_HEADER *dos_hdr;
	IMAGE_NT_HEADERS *nt_hdrs;
	IMAGE_EXPORT_DIRECTORY *edt;

	// Search for the loader data for NTDLL
	ldr = peb->Ldr;
	head = &ldr->InMemoryOrderModuleList;
	for (cur = head->Flink; cur != head; cur = cur->Flink) {
		cur_dll = CONTAINING_RECORD(cur, LDR_DATA_TABLE_ENTRY,
					    InMemoryOrderLinks);
		if (wcscasecmp(cur_dll->FullDllName.Buffer,
			       L"C:\\Windows\\System32\\ntdll.dll") == 0)
			break;
	}

	// Locate ntdll
	__ntdll = cur_dll->DllBase;
	dos_hdr = (IMAGE_DOS_HEADER *)__ntdll;
	nt_hdrs = (IMAGE_NT_HEADERS *)(__ntdll + dos_hdr->e_lfanew);
	edt = __get_export_dir(__ntdll);

	// Detect if this is Windows 7
	__is_windows_7 = nt_hdrs->OptionalHeader.MajorImageVersion <= 6 &&
			 nt_hdrs->OptionalHeader.MinorImageVersion <= 2;

	// Load other important functions, and kernel32
	__LdrGetProcedureAddress =
		__load_symbol(__ntdll, edt, "LdrGetProcedureAddress");
	__LdrLoadDll = __load_symbol(__ntdll, edt, "LdrLoadDll");
	__LdrUnloadDll = __load_symbol(__ntdll, edt, "LdrUnloadDll");

	__NtAllocateVirtualMemory =
		__load_symbol(__ntdll, edt, "NtAllocateVirtualMemory");
	__NtCloseHandle = __load_symbol(__ntdll, edt, "NtCloseHandle");
	__NtFreeVirtualMemory =
		__load_symbol(__ntdll, edt, "NtFreeVirtualMemory");
	__NtOpenProcess = __load_symbol(__ntdll, edt, "NtOpenProcess");
	__NtProtectVirtualMemory =
		__load_symbol(__ntdll, edt, "NtProtectVirtualMemory");
	__NtQueryInformationProcess =
		__load_symbol(__ntdll, edt, "NtQueryInformationProcess");
	__NtQuerySystemInformation =
		__load_symbol(__ntdll, edt, "NtQuerySystemInformation");
	__NtTerminateProcess =
		__load_symbol(__ntdll, edt, "NtTerminateProcess");

	// Get kernel32's base address
	__LdrLoadDll(NULL, NULL,
		     &(UNICODE_STRING)RTL_CONSTANT_STRING(L"kernel32.dll"),
		     &__kernel32);
}

_LIBC_DLLSYM uint32_t __get_symbol_ordinal(void *base,
					   IMAGE_EXPORT_DIRECTORY *edt,
					   const char *name)
{
	uint32_t *npt;
	int cmp;
	uint32_t max;
	uint32_t mid;
	uint32_t min;

	// Get the name pointer table and export ordinal table
	npt = (uint32_t *)((uint8_t *)base + edt->AddressOfNames);

	// Do a binary search for the function
	min = 0;
	max = edt->NumberOfNames - 1;
	while (min <= max) {
		mid = (min + max) >> 1;
		cmp = strcmp((const char *)((uint8_t *)base + npt[mid]), name);
		if (cmp < 0)
			min = mid + 1;
		else if (cmp > 0)
			max = mid - 1;
		else
			return mid + edt->Base + 1;
	}

	return UINT32_MAX;
}

_LIBC_DLLSYM IMAGE_EXPORT_DIRECTORY *__get_export_dir(void *base)
{
	uint8_t *base2 = base;
	IMAGE_DOS_HEADER *dos_hdr;
	IMAGE_NT_HEADERS *nt_hdrs;

	dos_hdr = (IMAGE_DOS_HEADER *)base2;
	nt_hdrs = (IMAGE_NT_HEADERS *)(base2 + dos_hdr->e_lfanew);
	return (IMAGE_EXPORT_DIRECTORY
			*)(base2 +
			   nt_hdrs->OptionalHeader
				   .DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]
				   .VirtualAddress);
}

_LIBC_DLLSYM void *__load_symbol(void *base, IMAGE_EXPORT_DIRECTORY *edt,
				 const char *symbol)
{
	ANSI_STRING name;
	void *func = NULL;
	uint32_t *funcs = (uint32_t *)(__ntdll + edt->AddressOfFunctions);
	uint32_t ord;

	if (!__LdrGetProcedureAddress) {
		// Look up the function in the table of function
		ord = __get_symbol_ordinal(base, edt, symbol) - edt->Base;
		if (__is_windows_7 && base == __ntdll)
			ord += 7; // Determined through trial and error
		func = (uint8_t *)base + funcs[ord];
	} else {
		// Fill the string
		name.Buffer = (char *)symbol;
		name.Length = strlen(symbol);
		name.MaximumLength = name.Length + 1;

		// Call LdrGetProcedureAddress
		__LdrGetProcedureAddress(base, &name, 0, &func);
	}

	return func;
}
