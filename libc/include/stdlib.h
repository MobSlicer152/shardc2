#pragma once

// stddef is a freestanding header, so I not only don't have to but shouldn't implement it
#include <stddef.h>

#if defined _X86 || defined _X86_64
typedef unsigned long long __reg_size_t;
#endif

// Perform a binary search on a sorted (i.e. by qsort) array
extern void *bsearch(const void *key, const void *base, size_t n, size_t size,
	      int (*cmp)(const void *a, const void *b));

// Convert a wide character string to an ASCII string
// (I don't understand character encodings well enough for wcstombs)
extern size_t wcstostr(char *restrict dst, const wchar_t *restrict src,
		       size_t n);

#if defined _X86 || defined _X86_64
// Execute the CPUID instruction and place the values of the registers
// into pointed to locations
extern void _cpuid(__reg_size_t rax_in, __reg_size_t rcx_in, __reg_size_t *rax, __reg_size_t *rbx, __reg_size_t *rcx, __reg_size_t *rdx);
#endif

