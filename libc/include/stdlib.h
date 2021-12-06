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

// This has to be in every header
#include "internal/compiler_fixups.h"

// stddef is a freestanding header, so I not only don't have to but shouldn't implement it
#include <stddef.h>

// Magic number for validating allocated pointers
#define _ALLOC_MAGIC 0x434947414D // MAGIC in ASCII

// Check if an allocation's magic number is valid
#define _ALLOC_IS_VALID(alloc_info) (alloc_info && alloc_info->magic == _ALLOC_MAGIC)

// Get the real size of an allocation (i.e. without the metadata)
#define _ALLOC_REAL_SIZE(alloc_info) (alloc_info->size - sizeof(struct __alloc_info))

// Information for malloc'd chunks
struct __alloc_info {
	unsigned long long magic; // Magic value to detect valid chunks
	size_t size; // Original size
	_Bool is_free; // Whether this chunk is free
	struct __alloc_info *next; // Next chunk. NULL if this is the last one
};

// Perform a binary search on a sorted (i.e. by qsort) array
_LIBC_DLLSYM void *bsearch(const void *key, const void *base, size_t n, size_t size,
	      int (*cmp)(const void *guess, const void *key));

// Convert a wide character string to an ASCII string
// (I don't understand character encodings well enough for wcstombs).
// Returns the number of characters converted, including the terminating NULL
_LIBC_DLLSYM size_t wcstostr(char *restrict dst, const wchar_t *restrict src,
		       size_t n, char invalid_replacement);

// Exit, calling atexit functions
_LIBC_DLLSYM _Noreturn void exit(int status);

// Exit without calling atexit functions
_LIBC_DLLSYM _Noreturn void _Exit(int status);

// Allocate n bytes of heap space
_LIBC_DLLSYM void *malloc(size_t n);

// Allocate and zero n elements of size bytes each
_LIBC_DLLSYM void *calloc(size_t n, size_t size);

// Free an allocation
_LIBC_DLLSYM void free(void *chunk);

#if defined _X86 || defined _X86_64
// Execute the CPUID instruction and place the values of the registers
// into pointed to locations
_LIBC_DLLSYM void _cpuid(__reg_size_t rax_in, __reg_size_t rcx_in, __reg_size_t *rax, __reg_size_t *rbx, __reg_size_t *rcx, __reg_size_t *rdx);
#endif

// Macros for manipulating integers
#define __qhaszero(n) (((n) - 0x0101010101010101) & ~(n) & 0x8080808080808080)
