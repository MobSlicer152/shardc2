// Miscellaneous utility functions
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

// stddef is a freestanding header, so I not only don't have to but shouldn't implement it
#include <stddef.h>

// Structure to store allocation details
#define _ALLOC_MAGIC 42069
struct __alloc_info {
	short magic; // Magic value to detect valid chunks
	size_t size; // Original size
	_Bool is_free; // Whether this chunk is free
	struct __alloc_info *next; // Next chunk. NULL if this is the last one
};

#if defined _X86 || defined _X86_64
typedef unsigned long long __reg_size_t;
#endif

// Perform a binary search on a sorted (i.e. by qsort) array
extern void *bsearch(const void *key, const void *base, size_t n, size_t size,
	      int (*cmp)(const void *guess, const void *key));

// Convert a wide character string to an ASCII string
// (I don't understand character encodings well enough for wcstombs)
extern size_t wcstostr(char *restrict dst, const wchar_t *restrict src,
		       size_t n);

// Exit, calling atexit functions
extern _Noreturn void exit(int status);

// Exit without calling atexit functions
extern _Noreturn void _Exit(int status);

// Allocate heap space (free the pointer after)

// Free an allocation
extern void free(void *chunk);

#if defined _X86 || defined _X86_64
// Execute the CPUID instruction and place the values of the registers
// into pointed to locations
extern void _cpuid(__reg_size_t rax_in, __reg_size_t rcx_in, __reg_size_t *rax, __reg_size_t *rbx, __reg_size_t *rcx, __reg_size_t *rdx);
#endif

// Macros for manipulating integers
#define __qhaszero(n) (((n) - 0x0101010101010101) & ~(n) & 0x8080808080808080)
