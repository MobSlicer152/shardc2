// String conversion functions
//
// Copyright 2022 MobSlicer152
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

#include <limits.h>

_LIBC_DLLSYM size_t wcstostr(char *restrict dst, const wchar_t *restrict src, size_t n, char invalid_replacement)
{
	size_t i;

	// Process each character
	for (i = 0; i < n && src[i] != L'\0'; i++) {
		if (src[i] < UCHAR_MAX)
			dst[i] = (char)(src[i] & UCHAR_MAX);
		else
			dst[i] = invalid_replacement;
	}

	// Add a NULL terminator
	i++;
	dst[i] = '\0';

	// Return the number of characters processed
	return i;
}
