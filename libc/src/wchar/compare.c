#include "wchar.h"

int wcscasecmp(const wchar_t *s1, const wchar_t *s2)
{
	wchar_t c1 = towlower(*s1);
	wchar_t c2 = towlower(*s2);

	while (*s1 != L'\0' && *s2 != L'\0') {
		// Compare
		if (c1 != c2)
			break;

		// Advance the pointers
		c1 = towlower(*s1++);
		c2 = towlower(*s2++);
	}

	return c1 - c2;
}
