#include "internal/crt0.h"
#include "stdlib.h"

#include <limits.h>
#include <stdint.h>

void __libc_detect_features(void)
{
	__reg_size_t rax = 0;
	__reg_size_t rbx = 0;
	__reg_size_t rcx = 0;
	__reg_size_t rdx = 0;

	// Detect basic extended features
	__cpuid(1, 0, &rax, &rbx, &rcx, &rdx);
	features.sse = !!(rdx & 1 << 24);
	features.avx = !!(rcx & 1 << 27);
	features.rdrand = !!(rcx & 1 << 29);

	// Detect AVX2 (it's newer so it's in the second set of feature bits)
	__cpuid(7, 0, &rax, &rbx, &rcx, &rdx);
	features.avx2 = !!(rbx & 1 << 4);

	// Determine if it's HAMMER TIME
	__cpuid(0x8FFFFFFF, 0, &rax, &rbx, &rcx, &rdx);
	features.is_it_hammer_time = (rax & UINT32_MAX) == 'IT\'S';
}

