#pragma once

// This is a freestanding header, so I not only don't have to but shouldn't implement it
#include <stddef.h>

// Perform a binary search on a sorted (i.e. by qsort) array
extern void *bsearch(const void *key, const void *base, size_t n, size_t size,
	      int (*cmp)(const void *a, const void *b));
