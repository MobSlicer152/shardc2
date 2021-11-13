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

void mainCRTStartup(void)
{
	int ret = 0;
	UNICODE_STRING *cmdline;
	wchar_t **argv_w;
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
	cmdline = &__peb->ProcessParameters->CommandLine;
	argv_w = __CommandLineToArgvW(cmdline->Buffer, &argc);
	argv = calloc(argc, sizeof(char *));
	for (i = 0; i < argc; i++) {
		size_t arg_len = wcslen(argv_w[i]);
		argv[i] = calloc(arg_len + 1, sizeof(char));
		wcstostr(argv[i], argv_w[i], arg_len, '.');
	}

	// Free the wide arguments
	__LocalFree(argv_w);

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
