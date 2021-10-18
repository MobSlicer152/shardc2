// Windows entry point and initialization
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

#include "internal/crt0.h"

#include "internal/win32/defs.h"
#include "internal/win32/ldr.h"

PEB *__peb;
struct __cpu_features __features;

void mainCRTStartup(void)
{
	int ret = 0;
	UNICODE_STRING cmdline;

	// First get the PEB
	__peb = _PEB_LOC;

	// Detect CPU features
	__libc_detect_features();

	// Now load functions used throughout the library
	__load_lib_dep_funcs(__peb);

	// Convert the commandline to argv
	cmdline = __peb->ProcessParameters->CommandLine;

	// Exit
	exit(ret);
}
