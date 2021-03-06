// Tests the entry point and the calling of the main function
//
// Copyright 2022 MobSlicer152
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

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

int main(int argc, char *argv[])
{
	char a[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char *b;

	b = calloc(ARRAY_SIZE(a), sizeof(char));

	memcpy(b, a, ARRAY_SIZE(a));
	memset(b, 'b', ARRAY_SIZE(a));

#ifdef __linux__
	for (int i = 0; i < argc; i++) {
		write(1, argv[i], strlen(argv[i]));
		write(1, "\n", 1);
	}
#endif

	free(b);

	return argc;
}
