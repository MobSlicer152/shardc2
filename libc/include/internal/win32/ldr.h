// Functions for loading functions using the dynamic linker
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

#pragma once

#include "defs.h"

extern uint8_t *__ntdll;
extern uint8_t *__kernel32;

// Initialization function that loads functions from NTDLL and Kernel32 used by the library
extern void __load_lib_dep_funcs(PEB *peb);

// Get the ordinal of a function by name (returns UINT32_MAX on failure)
extern uint32_t __get_symbol_ordinal(void *base, IMAGE_EXPORT_DIRECTORY *edt,
				   const char *name);

// Loads an exported symbol from the DLL mapped at base
extern void *__load_symbol(void *base, IMAGE_EXPORT_DIRECTORY *edt, const char *symbol);

// Function pointers that are loaded for use by the library
extern long (*__LdrGetProcedureAddress)(void *base, ANSI_STRING *name,
				      unsigned long ord, void **func_out);
extern long (*__LdrLoadDll)(wchar_t *path, unsigned long *characteristics,
			  UNICODE_STRING *name, void **base_out);
extern long (*__LdrUnloadDll)(void *base);
extern long (*__NtTerminateProcess)(uint64_t handle, uint32_t status);
