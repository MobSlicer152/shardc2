#pragma once

// Initialization function that loads functions from NTDLL and Kernel32 used by the library
extern void __load_lib_dep_funcs(PEB *peb);

// Loads an exported symbol from the DLL mapped at base
extern void *__load_symbol(void *base, const char *symbol);
