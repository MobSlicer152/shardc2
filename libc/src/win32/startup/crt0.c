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
bool __is_windows_7;

void mainCRTStartup(void)
{
	int ret = 0;
	UNICODE_STRING cmdline;
	wchar_t *cmdline2;
	wchar_t *cmdline3;
	char **argv;
	int argc = 0;
	size_t i;

	// First get the PEB
	__peb = _PEB_LOC;

	// Detect CPU features
	__libc_detect_features();

	// Now load functions used throughout the library
	__load_lib_dep_funcs(__peb);

	// Convert the commandline to argv
	cmdline = __peb->ProcessParameters->CommandLine;
	cmdline2 = calloc(cmdline.MaximumLength, sizeof(wchar_t));
	wcsncpy(cmdline2, cmdline.Buffer, cmdline.Length);
	for (i = 0; i < cmdline.Length; i++) {
		// Skip whitespace
		while (i + 1 < cmdline.Length && cmdline2[i + 1] == L' ' ||
		       cmdline2[i + 1] == L'\t')
			i++;
		if (i < cmdline.Length && cmdline2[i] == L' ' ||
		    cmdline2[i] == L'\t') {
			argc++;
			cmdline2[i] = '\0';
		}
	}
	argv = calloc(argc, sizeof(char *));
	cmdline3 = cmdline2;
	for (i = 0; i < argc && cmdline3 - cmdline2 < cmdline.Length; i++) {
		size_t arg_len = wcslen(cmdline3) + 1;

		// Convert this argument, then advance the pointer
		argv[i] = calloc(arg_len, sizeof(char));
		wcstostr(argv[i], cmdline3, arg_len, '.');
		cmdline3 += arg_len;
	}

	// Call main
	ret = main(argc, argv);

	// Free argv
	for (i = 0; i < argc; i++) {
		if (argv[i])
			free(argv[i]);
	}
	free(argv);

	// Exit
	exit(ret);
}
