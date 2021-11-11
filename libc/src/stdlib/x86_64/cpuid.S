;  SysV wrapper for the CPUID instruction
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

SECTION .text

GLOBAL _cpuid
_cpuid:
	push rbp
	mov rbp, rsp
	push rbx

	; Back up the parameters in RCX and RDX
	push rdx
	push rcx

	; Put the values desired for RAX and RCX in the right places
	mov rax, rdi
	mov rcx, rsi

	; Call cpuid
	cpuid

	; Move the results into the pointers given
	pop r11
	mov QWORD [r11], rax
	pop r11
	mov QWORD [r11], rbx
	mov QWORD [r8], rcx
	mov QWORD [r9], rdx

	pop rbx
	leave
	ret
