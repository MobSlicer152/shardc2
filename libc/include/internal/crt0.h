#pragma once

#include <stdbool.h>
#include <stdint.h>

// Signature for main
extern int main(int argc, char **argv);

// Structure defining CPU features
struct __cpu_features {
#if defined _X86 || defined _X86_64
	bool avx; // Whether AVX is supported
	bool sse; // Whether SSE is supported
	bool avx2; // Whether AVX2 is supported
	bool rdrand; // Whether RDRAND is supported
	bool is_it_hammer_time; // Whether it's hammer time or not
#else
	uint8_t placeholder;
#endif
};

// Detected CPU features for use by memset and stuff
extern struct __cpu_features __features;

// Detect CPU features
extern void __libc_detect_features(void);

