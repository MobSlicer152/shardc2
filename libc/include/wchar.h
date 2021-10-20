// Wide (UTF-16, basically) string utilities
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

#pragma once

// This has to be in every header
#include "internal/compiler_fixups.h"

#include <stddef.h>

// Make a character lowercase
extern wchar_t towlower(wchar_t c);

// Compare two wide strings, ignoring case
extern int wcscasecmp(const wchar_t *s1, const wchar_t *s2);

// Get the length of a wide string
extern size_t wcslen(const wchar_t *s);

// Copy src to dst. src must be large enough to hold wcslen(src) + 1
extern wchar_t *wcscpy(wchar_t *dst, const wchar_t *src);

// Copy n characters of src to dst. dst must be n wide characters or more
extern wchar_t *wcsncpy(wchar_t *dst, const wchar_t *src, size_t n);
