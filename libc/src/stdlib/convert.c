#include "stdlib.h"

#include <limits.h>

size_t wcstostr(char *restrict dst, const wchar_t *restrict src, size_t n)
{
	size_t i;

	// Process each character
	for (i = 0; i < n; i++) {
		if (src[i] < CHAR_MAX)
			dst[i] = (char)src[i] & 0xFF;
		else
			return (size_t)-1; // This is taken from wcstombs's behaviour
	}

	// Return the number of characters processed
	return i;
}
