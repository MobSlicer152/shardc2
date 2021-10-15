#include "internal/crt0.h"

#include "internal/win32/defs.h"
#include "internal/win32/ldr.h"

PEB *__peb;
struct __cpu_features __features;

void mainCRTStartup(void)
{
	int ret = 0;
	UNICODE_STRING cmdline;

	// First get the PEB
	__peb = _PEB_LOC;

	// Detect CPU features
	__libc_detect_features();

	// Now load functions used throughout the library
	__load_lib_dep_funcs(__peb);

	// Convert the commandline to argv
	cmdline = __peb->ProcessParameters->CommandLine;

	// Exit
	exit(ret);
}
