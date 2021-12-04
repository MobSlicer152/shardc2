// mmap abstraction for malloc
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

#include "internal/crt0.h"

#include "sys/mman.h"
#include "stdint.h"
#include "unistd.h"

_LIBC_DLLSYM void *__alloc(size_t *size)
{
	uint8_t *ret;

	// mmap
	ret = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ret == MAP_FAILED || ((int64_t)ret < 0 && (int64_t)ret > -4096)) {
		*size = 0;
		ret = NULL;
	}

	return ret;
}

_LIBC_DLLSYM void __free(void *chunk, size_t size)
{
	munmap(chunk, size);
}

