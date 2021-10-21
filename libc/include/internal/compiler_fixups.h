#pragma once

#ifdef _LIBC_BUILD
#ifdef _MSC_VER
#define _LIBC_DLLSYM __declspec(dllexport)
#else
#define _LIBC_DLLSYM
#endif
#else
#ifdef _MSC_VER
#define _LIBC_DLLSYM extern __declspec(dllimport)
#define _ACRTIMP __declspec(dllimport)
#else
#define _LIBC_DLLSYM extern
#endif
#endif

// Check for legacy MSVC
#if _MSC_VER < 1928
#define _COMPILER_IS_OLD_AF 1
#endif
#define _Noreturn

#ifdef _COMPILER_IS_OLD_AF

// MSVC problems
#ifdef _MSC_VER
#define restrict __restrict
#endif
#endif
