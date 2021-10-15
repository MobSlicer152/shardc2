#include <wchar.h>

wint_t towlower(wint_t c)
{
	wint_t c2 = c;

	if (c2 >= L'A' && c2 <= L'Z')
		c2 += L' ';

	return c2;
}
