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
