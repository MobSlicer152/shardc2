#pragma once

// The standard basically expects this header to include stddef
#include <stddef.h>

// Copy n bytes of src to dst
extern void *memcpy(void *restrict dst, const void *restrict src, size_t n);

// Length of a string
