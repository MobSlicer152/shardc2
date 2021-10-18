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
uint8_t *__ntdll;
uint8_t *__kernel32;

// Function pointers
long (*__LdrGetProcedureAddress)(void *base, ANSI_STRING *name,
				 unsigned long ord, void **func_out) = 0;
long (*__LdrLoadDll)(wchar_t *path, unsigned long *characteristics,
		     UNICODE_STRING *name, void **base_out) = 0;
long (*__LdrUnloadDll)(void *base) = 0;
long (*__NtTerminateProcess)(uint64_t handle, uint32_t status) = 0;

void __load_lib_dep_funcs(PEB *peb)
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

	// Locate LdrGetProcedureAddress by hand
	__ntdll = cur_dll->DllBase;
	dos_hdr = (IMAGE_DOS_HEADER *)__ntdll;
	nt_hdrs = (IMAGE_NT_HEADERS *)(__ntdll + dos_hdr->e_lfanew);
	edt = (IMAGE_EXPORT_DIRECTORY
		       *)(__ntdll +
			  nt_hdrs->OptionalHeader
				  .DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]
				  .VirtualAddress);

	// Load other important functions, and kernel32
	__LdrGetProcedureAddress = __load_symbol(__ntdll, edt, "LdrGetProcedureAddress");
	__LdrLoadDll = __load_symbol(__ntdll, edt, "LdrLoadDll");
	__LdrUnloadDll = __load_symbol(__ntdll, edt, "LdrUnloadDll");
	__NtTerminateProcess = __load_symbol(__ntdll, edt, "NtTerminateProcess");

	// Get kernel32's base address
	__LdrLoadDll(NULL, NULL, &(UNICODE_STRING)RTL_CONSTANT_STRING(L"kernel32.dll"), &__kernel32);
}

uint32_t __get_symbol_ordinal(void *base, IMAGE_EXPORT_DIRECTORY *edt,
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

void *__load_symbol(void *base, IMAGE_EXPORT_DIRECTORY *edt, const char *symbol)
{
	ANSI_STRING name;
	void *func = NULL;
	uint32_t *funcs = (uint32_t *)(__ntdll + edt->AddressOfFunctions);

	if (!__LdrGetProcedureAddress) {
		// Look up the function in the table of functions
		func = (uint8_t *)base + funcs[__get_symbol_ordinal(base, edt, symbol) - edt->Base];
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
