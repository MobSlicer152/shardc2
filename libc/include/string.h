#pragma once

// The standard basically expects this header to include stddef
#include <stddef.h>

// All the non-POSIX functions in the header are provided by MSVC. but I don't want to use them
#ifdef _MSC_VER
#pragma function(memcpy)
#pragma function(strlen)
#endif

// Copy n bytes of src to dst
extern void *memcpy(void *restrict dst, const void *restrict src, size_t n);

// Get the length of s
extern size_t strlen(const char *s);

