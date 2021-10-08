#include "internal/crt0.h"

struct __cpu_features features;

void __libc_linux_init(int argc, char **argv)
{
	int ret;

	// Detect CPU features
	__libc_detect_features();

	// Call main
	ret = main(argc, argv);
}

