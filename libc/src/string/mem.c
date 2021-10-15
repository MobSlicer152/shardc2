#include "string.h"

#include <stdint.h>

void *memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t i;

	// Copy bytes
	for (i = 0; (uint64_t)src % sizeof(uint64_t) != 0 &&
		    (uint64_t)dst % sizeof(uint64_t) != 0 && i < n;
	     i++)
		((uint8_t *)dst)[i] = ((uint8_t *)src)[i];

	// 

	return dst;
}
