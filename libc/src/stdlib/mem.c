// Implementation of malloc and other memory related functions
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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "internal/crt0.h"

// Start of the linked list of allocated chunks
static struct __alloc_info *__malloc_chunk_list_head = NULL;

// Allocate a new chunk with __alloc and do some pointer arithmetic. n can be zero
struct __alloc_info *__malloc_get_new_chunk(size_t n);

// Defragment adjacent free chunks
void __malloc_defrag_chunk_list(void);

// Find a free chunk or allocates a new one. Will defragment free chunks with __malloc_defrag_chunk_list
struct __alloc_info *__malloc_find_free_chunk(size_t size);

_LIBC_DLLSYM void *malloc(size_t n)
{
	struct __alloc_info *info;

	// Return NULL if the size is 0
	if (!n)
		return NULL;

	// Search for a free chunk
	info = __malloc_find_free_chunk(n);

	// Return the start of the allocation
	return info ? ++info : NULL;
}

_LIBC_DLLSYM void *calloc(size_t n, size_t size)
{
	void *ret;
	size_t real_size = n * size;

	// malloc a new chunk
	ret = malloc(real_size);
	if (ret)
		memset(ret, 0, real_size);

	return ret;
}

_LIBC_DLLSYM void free(void *chunk)
{
	struct __alloc_info *info =
		(struct __alloc_info *)((uint8_t *)chunk -
					sizeof(struct __alloc_info));

	// Check the magic
	if (!chunk || !_ALLOC_IS_VALID(info))
		return;

	// Mark the chunk as free
	info->is_free = true;

	// Defrag the chunk list
	__malloc_defrag_chunk_list();
}

struct __alloc_info *__malloc_get_new_chunk(size_t size)
{
	struct __alloc_info *ret;
	size_t real_size = sizeof(struct __alloc_info) + size;

	// Allocate the new chunk
	ret = __alloc(&real_size);
	if (!ret)
		return NULL;

	// Fill in the chunk
	ret->magic = _ALLOC_MAGIC;
	ret->size = real_size;
	ret->is_free = false;
	ret->next = __malloc_chunk_list_head;
	__malloc_chunk_list_head = ret;

	return ret;
}

void __malloc_defrag_chunk_list(void)
{
	struct __alloc_info *cur;

	// Go through the list
	for (cur = __malloc_chunk_list_head; cur; cur = cur->next) {
		// Check if the next chunk is free and in this chunk
		if (cur->next && cur->is_free && cur->next->is_free &&
		    ((uint8_t *)cur + cur->size) == (uint8_t *)cur->next) {
			// Absorb the next chunk
			cur->size += cur->next->size;
			cur->next = cur->next->next;
		}
	}
}

struct __alloc_info *__malloc_find_free_chunk(size_t size)
{
	struct __alloc_info *cur;
	struct __alloc_info *split;
	bool found = false;

	// Defragment the list
	__malloc_defrag_chunk_list();

	// Traverse the list and try to find a big enough chunk
	for (cur = __malloc_chunk_list_head; cur; cur = cur->next) {
		// Check if we found a suitable chunk
		if (cur->is_free && _ALLOC_REAL_SIZE(cur) >= size) {
			found = true;
			break;
		}
	}

	// If no usable chunk was found, get a new one
	if (!found) {
		cur = __malloc_get_new_chunk(size);
		if (!cur)
			return NULL;
	}

	// Split the chunk if possible
	if (cur->size > (sizeof(struct __alloc_info) + size)) {
		split = (struct __alloc_info *)((uint8_t *)cur +
						sizeof(struct __alloc_info) +
						size);
		split->magic = _ALLOC_MAGIC;
		split->size = cur->size - (sizeof(struct __alloc_info) + size);
		split->is_free = true;
		split->next = cur->next;
		cur->next = split;
		cur->size = size;
	}

	// Mark this chunk as in use
	cur->is_free = false;

	// Return the chunk
	return cur;
}
