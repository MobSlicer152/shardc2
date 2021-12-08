;  MASM memcpy implementation for x86
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

.data
INCLUDE internal/win32/asmdefs.asm

; Detected features from mainCRTStartup
EXTERN __features:__cpu_features

.code

memcpy PROC
	; Stack setup
	push rbp
	mov rbp, rsp

	; Save RCX and RDX
	mov r10, rdx
	mov r12, rcx

	; Clear R14 to use as a counter
	xor r14d, r14d

	; Check for SSE and AVX
	lea rcx, __features
	mov dl, (__cpu_features PTR [rcx]).avx
	cmp dl, 1
	je ymm_setup
	mov dl, (__cpu_features PTR [rcx]).sse
	cmp dl, 1
	je xmm_setup
	jmp SHORT byte_copy

	; Setup for different copy loops
	ymm_setup:
		; Check if n is large enough to use the AVX loop
		cmp r8, 32
		jle SHORT xmm_setup
		mov r9, 32 ; Alignment
		mov r13, ymm_copy_setup ; The label to jump to
		jmp SHORT byte_align_copy_setup ; Align the pointer by copying individual bytes
	xmm_setup:
		; Check n
		cmp r8, 16
		jle SHORT byte_copy
		mov r9, 16 ; Alignment
		mov r13, xmm_copy_setup
		jmp SHORT byte_align_copy_setup ; Align the pointer
	misaligned_fix:
		; Adjust the registers to continue copying
		mov r8, r11
		add r12, r14
		mov r14, 0
	byte_copy:
		; Check exit condition
		cmp r8, r14
		jae return

		; Copy
		mov r11, r10
		add r11, r14
		mov r9b, BYTE PTR [r11]
		sub r11, r10
		add r11, r12
		mov BYTE PTR [r11], r9b

		; Loop
		inc r14
		jmp SHORT byte_copy
	
	; Return, this point is only reached from byte_copy
	jmp return

	; Align the pointer by copying bytes
	byte_align_copy_setup:
		cmp r8, 0 ; Don't copy 0 bytes
		je SHORT byte_align_copy_end
	byte_align_copy:
		; Check exit condition
		xor edx, edx
		mov rax, r8
		mov r11, r9
		div r11
		cmp r14, rax
		ja SHORT byte_align_copy_end

		; Copy the value
		mov r11, r10
		add r11, r14
		push r9
		mov r9b, BYTE PTR [r11]
		sub r11, r10
		add r11, r12
		mov BYTE PTR [r11], r9b
		pop r9

		; Increase the counter
		mov r11, r14
		inc r11
		mov r14, r11
		jmp SHORT byte_align_copy
	byte_align_copy_end:

	; Make sure there's enough buffer for a big register
	mov r11, r8
	sub r11, r14
	cmp r11, r9
	jle misaligned_fix

	; R13 has the label that copies using SIMD
	jmp r13

	; Copy ymmwords
	ymm_copy_setup:
		mov r11, r12
		add r11, r14
		mov r9, r10
		add r9, r14
		mov rdx, r12
		add rdx, r8
		sub rdx, 1
		mov rcx, r10
		add rcx, r8
		sub rcx, 1
	ymm_copy:
		; Check the exit condition
		cmp r9, rcx
		jae SHORT ymm_copy_end
		cmp r11, rdx
		jae SHORT ymm_copy_end

		; Copy
		vmovdqu ymm0, YMMWORD PTR [r9]
		vmovdqu YMMWORD PTR [r11], ymm0

		; Increase the pointers
		add r9, 32
		add r11, 32
		jmp SHORT ymm_copy
	ymm_copy_end:
	jmp return

	; Copy ymmwords
	xmm_copy_setup:
		mov r11, r12
		add r11, r14
		mov r9, r10
		add r9, r14
		mov rdx, r12
		add rdx, r8
		sub rdx, 1
		mov rcx, r10
		add rcx, r8
		sub rcx, 1
	xmm_copy:
		; Check the exit condition
		cmp r9, rcx
		jae SHORT xmm_copy_end
		cmp r11, rdx
		jae SHORT xmm_copy_end

		; Copy
		movdqu xmm0, XMMWORD PTR [r9]
		movdqu XMMWORD PTR [r11], xmm0

		; Increase the pointers
		add r9, 16
		add r11, 16
		jmp SHORT xmm_copy
	xmm_copy_end:
	jmp return

	; Clean up
	return:
		mov rax, r12 ; dst gets returned
		pop r13
		pop r12
		leave
		ret
memcpy ENDP
PUBLIC memcpy

END
