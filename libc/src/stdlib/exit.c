#include "stdlib.h"

_Noreturn void exit(int status)
{
	_Exit(status);
}
