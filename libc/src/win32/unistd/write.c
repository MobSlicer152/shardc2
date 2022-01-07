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

_LIBC_DLLSYM size_t write(__register_size_t handle, void *buf, size_t len)
{
	IO_STATUS_BLOCK io_stat;

	__NtWriteFile(handle, NULL, NULL, NULL, &io_stat, buf, len, NULL, NULL);

	return io_stat.Information;
}

