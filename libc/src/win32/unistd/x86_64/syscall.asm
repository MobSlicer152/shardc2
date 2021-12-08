;  Windows NT system call wrapper
;
;  Copyright 2021 MobSlicer152
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

OPTION PROLOGUE:NONE

.code

__syscall PROC
	push rbp
	mov rbp, rsp

	; Shift parameters up
	mov eax, ecx
	mov r10, rdx ; the syscall instruction clobbers RCX, so it goes in R10
	mov rdx, r8
	mov r8, r9
	mov r9, QWORD PTR [rsp + 16]
	mov rcx, QWORD PTR [rsp + 24]
	mov QWORD PTR [rsp + 16], rcx
	mov rcx, QWORD PTR [rsp + 32]
	mov QWORD PTR [rsp + 24], rcx

	; Do the syscall
	syscall

	leave
	ret
__syscall ENDP
PUBLIC __syscall
