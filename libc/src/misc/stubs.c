// Compiler-specific stub functions
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

#include <stdint.h>

#if !defined __GNUC__ && !defined _MSC_VER
void __stack_chk_fail(void)
{
}
#endif // !__GNUC__ && !_MSC_VER

#ifdef _MSC_VER
void __GSHandlerCheck(void)
{
}

uintptr_t __security_cookie;
void __security_check_cookie(void)
{
}

void _RTC_InitBase(void)
{
}

void _RTC_Shutdown(void)
{
}
#endif
