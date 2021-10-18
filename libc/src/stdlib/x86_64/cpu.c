// x86-specific feature detection
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

#include "internal/crt0.h"
#include "stdlib.h"

#include <limits.h>
#include <stdint.h>

void __libc_detect_features(void)
{
	__reg_size_t rax = 0;
	__reg_size_t rbx = 0;
	__reg_size_t rcx = 0;
	__reg_size_t rdx = 0;

	// Detect basic extended features
	_cpuid(1, 0, &rax, &rbx, &rcx, &rdx);
	__features.sse = rdx & (1 << 25);
	__features.avx = rcx & (1 << 28);
	__features.rdrand = rcx & (1 << 30);

	// Detect AVX2 (it's newer so it's in the second set of feature bits)
	_cpuid(7, 0, &rax, &rbx, &rcx, &rdx);
	__features.avx2 = rbx & (1 << 5);

	// Determine if it's HAMMER TIME or not
	_cpuid(0x8FFFFFFF, 0, &rax, &rbx, &rcx, &rdx);
	__features.is_it_hammer_time = (rax & UINT32_MAX) == 'IT\'S';
}
