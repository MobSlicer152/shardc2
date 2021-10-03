#include "internal/crt0.h"

void __libc_linux_init(int argc, char **argv)
{
	int ret;

	// Call main
	ret = main(argc, argv);
}

