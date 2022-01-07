;  MASM wrapper for the CPUID instruction
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

OPTION PROLOGUE:NONE

.code

_cpuid PROC
	push rbp
	mov rbp, rsp
	push rbx
	
	; Place parameters in the right registers
	mov rax, rcx
	mov rcx, rdx

	; Call cpuid
	cpuid

	; Move the results into the pointers
	mov QWORD PTR [r8], rax
	mov QWORD PTR [r9], rbx
	mov r10, QWORD PTR [rbp + 48]
	mov QWORD PTR [r10], rcx
	mov r10, QWORD PTR [rbp + 56]
	mov QWORD PTR [r10], rdx

	pop rbx
	leave
	ret
_cpuid ENDP
PUBLIC _cpuid

END

