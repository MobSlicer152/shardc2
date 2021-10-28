// Comparison functions
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

#include "string.h"

#include <stdint.h>

#if !defined NDEBUG || !defined _MSC_VER
_LIBC_DLLSYM int memcmp(const void *b1, const void *b2, size_t n)
{
	size_t i;
	int ret;

	// Compare bytes
	for (i = 0; i < n; i++) {
		ret = ((uint8_t *)b1)[i] - ((uint8_t *)b2)[i];
		if (ret != 0)
			break;
	}

	if (ret < 0)
		return -1;
	else if (ret > 0)
		return 1;
	else
		return 0;
}

_LIBC_DLLSYM int strcmp(const char *s1, const char *s2)
{
	// They aren't equal if they're not the same length
	return memcmp(s1, s2, strlen(s1));
}
#endif
