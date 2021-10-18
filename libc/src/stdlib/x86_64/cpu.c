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
	_cpuid(1, 0, &rax, &rbx, &rcx, &rdx);
	__features.sse = rdx & (1 << 25);
	__features.avx = rcx & (1 << 28);
	__features.rdrand = rcx & (1 << 30);

	// Detect AVX2 (it's newer so it's in the second set of feature bits)
	_cpuid(7, 0, &rax, &rbx, &rcx, &rdx);
	__features.avx2 = rbx & (1 << 5);

	// Determine if it's HAMMER TIME or not
	_cpuid(0x8FFFFFFF, 0, &rax, &rbx, &rcx, &rdx);
	__features.is_it_hammer_time = (rax & UINT32_MAX) == 'IT\'S';
}
