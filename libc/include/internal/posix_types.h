// POSIX types
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

#ifdef __linux__
#include <asm/posix_types.h>

// Linux provides all these types
typedef __kernel_off_t off_t;
typedef __kernel_loff_t off64_t;
typedef __kernel_ssize_t ssize_t;
#endif

