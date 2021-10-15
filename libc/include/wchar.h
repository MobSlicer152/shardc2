#pragma once

#include <stddef.h>

// Make a character lowercase
extern wchar_t towlower(wchar_t c);

// Compare two wide strings, ignoring case
extern int wcscasecmp(const wchar_t *s1, const wchar_t *s2);

// Get the length of a wide string
extern size_t wcslen(const wchar_t *s);
