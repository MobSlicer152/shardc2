;  Linux entry point
;
;  Copyright 2021 MobSlicer152
;
;  Licensed under the Apache License, Version 2.0 (the "License");
;  you may not use this file except in compliance with the License.
;  You may obtain a copy of the License at
;
;      http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
;  distributed under the License is distributed on an "AS IS" BASIS,
;  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;  See the License for the specific language governing permissions and
;  limitations under the License.

BITS 64
DEFAULT REL

; C-side initialization
EXTERN __libc_linux_init

SECTION .text

GLOBAL _start
_start:
	; Put argc and argv in the appropriate registers
	pop rdi
	pop rsi

	call __libc_linux_init wrt ..plt

