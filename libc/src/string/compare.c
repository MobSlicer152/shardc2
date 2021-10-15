#include "string.h"

#include <stdint.h>

int memcmp(const void *b1, const void *b2, size_t n)
{
	size_t i;
	int ret;

	// Compare bytes
	for (i = 0; i < n; i++) {
		ret = ((uint8_t *)b1)[i] - ((uint8_t *)b2)[i];
		if (ret != 0)
			break;
	}

	if (ret < 0)
		return -1;
	else if (ret > 0)
		return 1;
	else
		return 0;
}

int strcmp(const char *s1, const char *s2)
{
	// They aren't equal if they're not the same length
	return memcmp(s1, s2, strlen(s1));
}
