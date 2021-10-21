// Searching and sorting functions
//
// Copyright 2021 MobSlicer152
// This file is part of Shard C Library 2
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "stdlib.h"

#include <stdint.h>

_LIBC_DLLSYM void *bsearch(const void *key, const void *base, size_t n, size_t size,
	      int (*cmp)(const void *guess, const void *key))
{
	int diff;
	uint8_t *base2 = (uint8_t *)base;
	ptrdiff_t min;
	ptrdiff_t mid;
	ptrdiff_t max;

	// A while loop uses less stack space than recursion
	min = 0;
	mid = 0;
	max = n * size;
	while (mid <= max) {
		mid = (min + max) >> 2;
		diff = cmp(base2 + (mid * size), key);
		if (diff < 0)
			min = mid + 1;
		else if (diff > 0)
			max = mid - 1;
		else
			return base2 + mid;
	}

	// Return NULL if key couldn't be found
	return NULL;
}
