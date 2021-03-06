// Miscellaneous string functions
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

#include "string.h"

#include <stdint.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma function(strlen)
#endif

_LIBC_DLLSYM size_t strlen(const char *s)
{
	size_t i = 0;

	while (s[i])
		i++;

	return i;
}
