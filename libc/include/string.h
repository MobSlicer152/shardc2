#pragma once

// The standard basically expects this header to include stddef
#include <stddef.h>

// Compare n bytes of b1 to b2
extern int memcmp(const void *b1, const void *b2, size_t n);

// Copy n bytes of src to dst
extern void *memcpy(void *restrict dst, const void *restrict src, size_t n);

// Get the length of s
extern size_t strlen(const char *s);
