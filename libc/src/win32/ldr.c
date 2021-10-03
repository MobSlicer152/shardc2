#include "internal/win32/defs.h"

void __load_lib_dep_funcs(PEB *peb)
{
	PEB_LDR_DATA *ldr;

	// Alias the loader data
	ldr = peb->Ldr;
}
