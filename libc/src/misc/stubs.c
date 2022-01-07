// Stubs and miscellaneous compiler-specific functions
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

#include <stdint.h>
#include <stdlib.h>

#if !defined __GNUC__ || !defined _MSC_VER
void __stack_chk_fail(void)
{
}
#endif

#ifdef _MSC_VER
void __GSHandlerCheck(void)
{
}

uintptr_t __security_cookie;

void __security_init_cookie(void)
{
#ifdef _M_X64
	__security_cookie = 0x6969696969696969;
#elif _M_IX86
	__security_cookie = 0x69696969;
#endif
}
#endif
