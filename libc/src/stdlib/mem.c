// Implementation of malloc and other memory related functions
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

#include "stdlib.h"

#include <stdbool.h>
#include <stdint.h>

// Start of the linked list of allocated chunks
struct __alloc_info *__malloc_chunk_list_head;

// Initialize stuff malloc needs
void __malloc_init(void);

// Allocate a new chunk with __alloc and do some pointer arithmetic. n can be zero
struct __alloc_info *__malloc_get_new_chunk(size_t n);

// Defragment adjacent free chunks
void __malloc_defrag_chunk_list(void);

// Find a free chunk or allocates a new one. Will defragment free chunks with __malloc_defrag_chunk_list
struct __alloc_info *__malloc_find_free_chunk(size_t size);

_LIBC_DLLSYM void *malloc(size_t n)
{
	struct __alloc_info *info;

	// Make sure the chunk list is initialized
	if (!__malloc_chunk_list_head)
		__malloc_init();

	// Return NULL if the size is 0
	if (!n)
		return NULL;

	// Search for a free chunk
	info = __malloc_find_free_chunk(n);

	// Return the start of the allocation
	return info--;
}

_LIBC_DLLSYM void *calloc(size_t n, size_t size)
{
	void *ret;

	// malloc a new chunk and zero it
	ret = malloc(n * size);
//	memset(ret, 0, n * size);

	return ret;
}

void __malloc_init(void)
{
	// Allocate the head of the chunk list and fill it in
	__malloc_chunk_list_head = __malloc_get_new_chunk(0);
	__malloc_chunk_list_head->basic_info.magic = _ALLOC_MAGIC;
	__malloc_chunk_list_head->is_free = false;
}

struct __alloc_info *__malloc_get_new_chunk(size_t size)
{
	struct __alloc_info *ret;

	// Allocate the new chunk
	ret = __alloc(sizeof(struct __alloc_info) -
			sizeof(struct __basic_alloc_info) + size);
	if (!ret)
		return NULL;

	// Fill in the chunk's data
	(uint8_t *)ret -= sizeof(struct __basic_alloc_info);
	ret->basic_info.magic = _ALLOC_MAGIC;
	ret->basic_info.size = size;
	ret->is_free = false;

	return ret;
}

void __malloc_defrag_chunk_list(void)
{
	struct __alloc_info *cur;

	// Go through the list
	for (cur = __malloc_chunk_list_head->next; cur; cur = cur->next) {
		// Check if the next chunk is free
		if (cur->is_free && cur->next->is_free) {
			cur->basic_info.size += cur->next->basic_info.size;
			cur->next = cur->next->next;
		}
	}
}

struct __alloc_info *__malloc_find_free_chunk(size_t size)
{
	struct __alloc_info *cur;
	struct __alloc_info *tmp;
	bool found;

	// Defragment the list
	__malloc_defrag_chunk_list();

	// Traverse the list and try to find a big enough chunk
	for (cur = __malloc_chunk_list_head->next; _ALLOC_IS_VALID(cur); cur = cur->next) {
		// Check if we found a suitable chunk
		if (cur->is_free == true && _ALLOC_REAL_SIZE(cur) >= size) {
			found = true;
			break;
		}
	}

	// If the next chunk is NULL and no usable chunk was found, get a new one
	if (!found && !cur->next) {
		tmp = __malloc_get_new_chunk(size);
		cur->next = tmp;
		tmp->next = NULL;
	}

	// Return the chunk
	return cur;
}

