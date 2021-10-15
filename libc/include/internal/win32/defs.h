#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

// Set the PHNT headers to target Windows 7, it's the best version
#define PHNT_VERSION PHNT_WIN7
#include <phnt_windows.h>
#include <phnt.h>

// The current process's PEB, defined in win32/crt0.c
extern PEB *__peb;

// Get a pointer to the PEB
#ifdef _M_IX86_
#define _PEB_LOC (PEB *const)__readfsdword(0x30)
#elif defined _M_X64
#define _PEB_LOC (PEB *const)__readgsqword(0x60)
#endif
