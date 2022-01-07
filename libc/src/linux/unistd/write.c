// write
//
// copyright 2022 mobslicer152
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

#include "unistd.h"

_LIBC_DLLSYM size_t write(uint64_t fd, void *buf, size_t len)
{
	return __syscall(__NR_write, fd, buf, len);
}

