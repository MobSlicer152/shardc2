// Definitions for startup things
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

#pragma once

// This has to be in every header
#include "internal/compiler_fixups.h"

#include <stdbool.h>
#include <stdint.h>

// Signature for main
extern int main(int argc, char **argv);

// Structure defining CPU features
struct __cpu_features {
#if defined _X86 || defined _X86_64
	bool avx; // Whether AVX is supported
	bool sse; // Whether SSE is supported
	bool avx2; // Whether AVX2 is supported
	bool rdrand; // Whether RDRAND is supported
	bool is_it_hammer_time; // Whether it's hammer time or not
#else
	uint8_t placeholder;
#endif
};

// Detected CPU features for use by memset and stuff
struct __cpu_features __features;

// Detect CPU features
_LIBC_DLLSYM void __libc_detect_features(void);

// Allocate memory for internal use
_LIBC_DLLSYM void *__alloc(size_t size);

// Get free memory
_LIBC_DLLSYM size_t __get_free_mem(void);

// Free memory returned by __alloc
_LIBC_DLLSYM void __free(void *chunk);
