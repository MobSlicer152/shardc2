#include "internal/crt0.h"

#include "internal/win32/defs.h"
#include "internal/win32/ldr.h"

PEB *__peb;

void mainCRTStartup(void)
{
	// First get the PEB
	__peb = _PEB_LOC;

	// Now load functions used throughout the library
	__load_lib_dep_funcs(__peb);
}
