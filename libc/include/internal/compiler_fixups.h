// Hacky preprocessor bullshit for compiler specifics
//
// Copyright 2022 MobSlicer152
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

#include <stdint.h>

#ifdef _LIBC_BUILD
#ifdef _MSC_VER
#define _LIBC_DLLSYM __declspec(dllexport)
#else
#define _LIBC_DLLSYM
#endif
#else
#ifdef _MSC_VER
#define _LIBC_DLLSYM extern __declspec(dllimport)

#ifndef _ACRTIMP
#define _ACRTIMP __declspec(dllimport)
#endif // !_ACRTIMP
#else
#define _LIBC_DLLSYM extern
#endif
#endif

// Architecture
#if defined __x86_64__ || defined _M_AMD64
#define _X86_64 1
#endif

// How wide a register is
#ifdef _X86_64
typedef uint64_t __reg_size_t;
#endif

// Check for legacy MSVC
#if _MSC_VER < 1928
#define _COMPILER_IS_OLD_AF 1
#endif

#ifdef _COMPILER_IS_OLD_AF

// MSVC problems
#ifdef _MSC_VER
#define _Noreturn
#define restrict __restrict
#endif
#endif
