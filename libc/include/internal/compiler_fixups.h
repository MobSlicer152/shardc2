#pragma once

// Check for legacy MSVC
#if _MSC_VER < 1928
#define _COMPILER_IS_OLD_AF 1
#endif

#ifdef _COMPILER_IS_OLD_AF
#define _Noreturn

// MSVC problems
#ifdef _MSC_VER
#define restrict __restrict
#endif
#endif
