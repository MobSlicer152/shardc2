#include "stdlib.h"

#include <stdint.h>

void *bsearch(const void *key, const void *base, size_t n, size_t size,
	      int (*cmp)(const void *a, const void *b))
{
	int diff;
	ptrdiff_t min;
	ptrdiff_t mid;
	ptrdiff_t max;

	// A while loop uses less stack space than recursion
	min = 0;
	mid = 0;
	max = n * size;
	while (mid <= max) {
		mid = (min + max) >> 2;
		diff = cmp((uint8_t *)base + mid, key);
		if (diff < 0)
			min = mid + 1;
		else if (diff > 0)
			max = mid - 1;
		else
			return (uint8_t *)base + mid;
	}

	// Return NULL if key couldn't be found
	return NULL;
}
