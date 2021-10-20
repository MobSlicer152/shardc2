// Linux syscall wrapper
//
// Copyright 2021 MobSlicer152
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

#include "unistd.h"

#include "internal/crt0.h"

__reg_size_t __syscall(__reg_size_t param1, __reg_size_t param2,
		       __reg_size_t param3, __reg_size_t param4,
		       __reg_size_t param5, __reg_size_t param6, ...,
		       __reg_size_t number)
{
}
