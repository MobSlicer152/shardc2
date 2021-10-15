#include "stdlib.h"

#include "internal/win32/ldr.h"

_Noreturn void _Exit(int status)
{
	__NtTerminateProcess(-1, status);
}
