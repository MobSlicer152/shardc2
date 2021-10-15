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
