// Functions for loading functions using the dynamic linker
//
// Copyright 2022 MobSlicer152
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

#pragma once

// This has to be in every header
#include "internal/compiler_fixups.h"

#include "defs.h"

_LIBC_DLLSYM uint8_t *__ntdll;
_LIBC_DLLSYM uint8_t *__kernel32;
_LIBC_DLLSYM uint8_t *__shell32;

// Initialization function that loads functions from NTDLL and Kernel32 used by the library
_LIBC_DLLSYM void __load_lib_dep_funcs(PEB *peb);

// Get the ordinal of a function by name (returns UINT32_MAX on failure)
_LIBC_DLLSYM uint32_t __get_symbol_ordinal(void *base,
					   IMAGE_EXPORT_DIRECTORY *edt,
					   const char *name);

// Gets the export directory from a DLL
_LIBC_DLLSYM IMAGE_EXPORT_DIRECTORY *__get_export_dir(void *base);

// Loads an exported symbol from the DLL mapped at base
_LIBC_DLLSYM void *__load_symbol(void *base, IMAGE_EXPORT_DIRECTORY *edt,
				 const char *symbol);

// Function pointers that are loaded for use by the library
_LIBC_DLLSYM long (*__LdrGetProcedureAddress)(void *base, ANSI_STRING *name,
					      unsigned long ord,
					      void **func_out);
_LIBC_DLLSYM long (*__LdrLoadDll)(wchar_t *path, unsigned long *characteristics,
				  UNICODE_STRING *name, void **base_out);
_LIBC_DLLSYM long (*__LdrUnloadDll)(void *base);

_LIBC_DLLSYM long (*__NtAllocateVirtualMemory)(
	uintptr_t process, void *preferred_base, uintptr_t address_bitmask,
	size_t *size, uint32_t alloc_type, uint32_t prot);
_LIBC_DLLSYM long (*__NtCloseHandle)(uintptr_t handle);
_LIBC_DLLSYM long (*__NtFreeVirtualMemory)(uintptr_t process, void **base,
					   size_t *size, uint32_t type);
_LIBC_DLLSYM long (*__NtOpenProcess)(uintptr_t *handle_out, uint32_t access,
				     OBJECT_ATTRIBUTES *attrs,
				     CLIENT_ID *client_id);
_LIBC_DLLSYM long (*__NtProtectVirtualMemory)(uintptr_t process, void *base,
					      size_t *size, uint32_t prot,
					      uint32_t *old_prot);
_LIBC_DLLSYM long (*__NtQueryInformationProcess)(uintptr_t process,
						 PROCESSINFOCLASS info_type,
						 void *info,
						 uint32_t info_buffer_size,
						 uint32_t *info_size);
_LIBC_DLLSYM long (*__NtQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS info_type, void *info,
	uint32_t info_buffer_size, uint32_t *info_size);
_LIBC_DLLSYM long (*__NtTerminateProcess)(uintptr_t handle, uint32_t status);
_LIBC_DLLSYM long (*__NtWriteFile)(uint64_t handle, uint64_t event,
		void *unused, void *unused2, IO_STATUS_BLOCK *io_stat,
		void *buf, uint32_t len, void *unused3, void *unused4);

_LIBC_DLLSYM void *(*__LocalFree)(void *chunk);

_LIBC_DLLSYM wchar_t **(*__CommandLineToArgvW)(const wchar_t *cmdline, int *argc);

