;  Linux system call wrapper
;
;  Copyright 2022 MobSlicer152
;
;  Licensed under the Apache License, Version 2.0 (the "License");
;  you may not use this file except in compliance with the License.
;  You may obtain a copy of the License at
;
;      http://www.apache.org/licenses/LICENSE-2.0
;
;  Unless required by applicable law or agreed to in writing, software
;  distributed under the License is distributed on an "AS IS" BASIS,
;  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;  See the License for the specific language governing permissions and
;  limitations under the License.

SECTION .text

GLOBAL __syscall
__syscall:
	push rbp
	mov rbp, rsp

	; Shift arguments around
	mov rax, rdi
	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	mov r10, r8 ; the syscall instruction clobbers RCX, so it goes in R10
	mov r8, r9
	mov r9, QWORD [rsp + 16]

	; Make the syscall
	syscall

	; Return
	leave
	ret

