// Miscellaneous non-string functions from string.h
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

#ifdef _MSC_VER
#pragma comment(linker, "/export:memcpy")
#pragma comment(linker, "/export:memset")

#pragma function(memcpy, memset)
#else // The SysV assembly version of memcpy isn't done yet
_LIBC_DLLSYM void *memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t i;

	// Copy bytes
	for (i = 0; i < n; i++)
		((uint8_t *)dst)[i] = ((const uint8_t *)src)[i];

	return dst;
}
#endif

