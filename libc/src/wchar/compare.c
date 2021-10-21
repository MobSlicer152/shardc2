// Wide string comparison functions
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

#include "wchar.h"

_LIBC_DLLSYM int wcscasecmp(const wchar_t *s1, const wchar_t *s2)
{
	wchar_t c1 = towlower(*s1);
	wchar_t c2 = towlower(*s2);

	while (*s1 != L'\0' && *s2 != L'\0') {
		// Compare
		if (c1 != c2)
			break;

		// Advance the pointers
		c1 = towlower(*s1++);
		c2 = towlower(*s2++);
	}

	return c1 - c2;
}
