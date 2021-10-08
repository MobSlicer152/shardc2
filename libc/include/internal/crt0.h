#pragma once

#include <stdint.h>

// Signature for main
extern int main(int argc, char **argv);

// Structure defining CPU features
struct __cpu_features {
#if defined _X86 || defined _X86_64
	uint8_t sse; // Whether SSE is supported
	uint8_t avx; // Whether AVX is supported
	uint8_t avx2; // Whether AVX2 is supported
	uint8_t rdrand; // Whether RDRAND is supported
	uint8_t is_it_hammer_time; // Whether it's hammer time or not
#endif
};

// Detected CPU features for use by memset and stuff
extern struct __cpu_features features;

// Detect CPU features
extern void __libc_detect_features(void);

