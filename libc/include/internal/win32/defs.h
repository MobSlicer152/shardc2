// General definitions for Windows functions
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

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

// Set the PHNT headers to target Windows 7, it's the best version
#define PHNT_VERSION PHNT_WIN7
#include <phnt_windows.h>
#include <phnt.h>

// The current process's PEB, defined in win32/crt0.c
PEB *__peb;

// Whether this is a Windows 7 system
bool __is_windows_7;

// Get a pointer to the PEB
#ifdef _M_IX86_
#define _PEB_LOC (PEB *const)__readfsdword(0x30)
#elif defined _M_X64
#define _PEB_LOC (PEB *const)__readgsqword(0x60)
#endif

// Get the base address of the image for the parent process
_LIBC_DLLSYM uint8_t *__get_parent_base(void);

// Get the subsystem of a PE image
_LIBC_DLLSYM uint16_t __get_image_subsystem(uint8_t *base);
