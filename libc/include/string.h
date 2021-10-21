// String and buffer related utilities
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

// The standard basically expects this header to include stddef
#include <stddef.h>

// Compare n bytes of b1 to b2
_LIBC_DLLSYM int memcmp(const void *b1, const void *b2, size_t n);

// Copy n bytes of src to dst
_LIBC_DLLSYM void *memcpy(void *restrict dst, const void *restrict src, size_t n);

// Initialize n bytes of b to c
_LIBC_DLLSYM void *memset(void *b, int c, size_t n);

// Get the length of s
_LIBC_DLLSYM size_t strlen(const char *s);
