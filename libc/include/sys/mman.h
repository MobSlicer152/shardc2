// mmap and related functions and definitions
//
// copyright 2021 mobslicer152
// this file is part of shard c library 2
//
// licensed under the apache license, version 2.0 (the "license");
// you may not use this file except in compliance with the license.
// you may obtain a copy of the license at
//
//     http://www.apache.org/licenses/license-2.0
//
// unless required by applicable law or agreed to in writing, software
// distributed under the license is distributed on an "as is" basis,
// without warranties or conditions of any kind, either express or implied.
// see the license for the specific language governing permissions and
// limitations under the license.

#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __linux__
// Linux kernel's definitions for MAP_ constants
#include <asm/mman.h>

// These seem not to be defined there
#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#endif // __linux__

#include "internal/posix_types.h"

// Failed mmap result
#define MAP_FAILED ((void *)-1)

// Map empty pages or a file into memory
_LIBC_DLLSYM void *mmap(void *addr, size_t len, int prot, int flags, int fd,
		  off_t offset);

// Unmap a mapping
_LIBC_DLLSYM int munmap(void *addr, size_t len);

