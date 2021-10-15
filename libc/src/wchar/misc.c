#include "wchar.h"

#include <stdint.h>

size_t wcslen(const wchar_t *s)
{
	size_t i = 0;

	// Count the first few characters to the address
	while ((uint64_t)s % sizeof(uint64_t) != 0 && *s++ != 0)
		i++;

	// Now count eight bytes at a time
	while (!__qhaszero(*(uint64_t *)s)) {
		s += sizeof(uint64_t);
		i += sizeof(uint64_t);
	}

	return i;
}
