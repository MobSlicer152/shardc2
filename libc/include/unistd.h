// System calls and some other stuff
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

#include <stddef.h>
#include <stdint.h>

#ifdef _MSC_VER
#include <internal/win32/defs.h>
#elif defined __linux__
#include <asm/unistd.h>
#endif // _MSC_VER

#include "internal/crt0.h"
#include "internal/compiler_fixups.h"
#include "internal/posix_types.h"

// Generic system call, good for when I was too
// lazy to make a wrapper (only supports 6 parameters).
// Note that while this does support Windows, you're probably
// better off just using __load_symbol. If you want the likelihood
// of this breaking to be lower, use __get_syscall_num to
// get the system call number for Windows.
_LIBC_DLLSYM __reg_size_t __syscall(__reg_size_t num, ...);

#ifdef _WIN32
// Get the system call number of an NtXxx function defined in NTDLL
_LIBC_DLLSYM __reg_size_t __get_syscall_num(void *func);
#endif
