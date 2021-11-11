;  MASM memset implementation for x86
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

.const

; Constant to fill a qword with the value
fill_const EQU 0101010101010101h

.data
INCLUDE internal/win32/asmdefs.asm

; Detected features from mainCRTStartup
EXTERN __features:__cpu_features

; Counter
i DQ 0

.code

memset PROC
	; Stack setup
	push rbp
	mov rbp, rsp
	push r12
	push r13

	; Save registers clobbered by DIV
	mov r10, rdx
	mov r12, rcx

	; Check how many bytes can be set at once
	lea rcx, __features
	mov dl, (__cpu_features PTR [rcx]).avx
	cmp dl, 1
	je ymm_setup
	mov dl, (__cpu_features PTR [rcx]).sse
	cmp dl, 1
	je xmm_setup
	jmp SHORT byte_copy

	; Setup for different loops
	ymm_setup:
		; First check if n is less than 32
		cmp r8, 32
		jle SHORT xmm_setup
		mov r9, 32 ; Align the address to 32 bytes
		mov r13, ymm_fill_static_word ; Set the label to jump to
		jmp SHORT byte_align_copy_setup
	xmm_setup:
		; Check n
		cmp r8, 16
		jle SHORT byte_copy
		mov r9, 16 ; Align the address to 16 bytes
		mov r13, xmm_fill_static_word ; Set the label to jump to
		jmp SHORT byte_align_copy_setup
	byte_copy:
		; Check exit condition (i < n)
		cmp r8, i
		jae return

		; Copy the value
		mov r11, r12
		add r11, i
		mov BYTE PTR [r11], r10b

		; Loop
		inc i
		jmp SHORT byte_copy
	; Return
	jmp return

	; Handle individual bytes until the pointer is aligned properly.
	byte_align_copy_setup:
		cmp r8, 0 ; Skip to avoid copying 1 byte if n is 0
		je SHORT byte_align_copy_end
	byte_align_copy:
		; Check the exit condition
		xor edx, edx
		mov rax, r8
		mov r11, r9
		div r11
		cmp r11, i
		ja SHORT byte_align_copy_end

		; Copy the value
		mov r11, r12
		add r11, i
		mov BYTE PTR [r11], r10b

		; Increase the counter
		inc i
		jmp SHORT byte_align_copy
	byte_align_copy_end:

	; R13 contains the label that sets the XMM/YMM register up
	jmp r13

	; Set up a static filled xmmword of the chosen value
	xmm_fill_static_word:
		cmp r10, 0
		je SHORT c_is_zero_xmm
		jmp SHORT c_is_not_zero_xmm
	c_is_zero_xmm:
		; Just zero the register
		xorps xmm0, xmm0
		jmp xmm_copy_setup
	c_is_not_zero_xmm:
		mov rcx, fill_const
		movzx r11, r10b
		imul rcx, r11
		movq xmm0, rcx
		movlhps xmm0, xmm0
		jmp xmm_copy_setup

	; Set up a ymmword
	ymm_fill_static_word:
		cmp r10, 0
		je SHORT c_is_zero_ymm
		jmp SHORT c_is_not_zero_ymm
	c_is_zero_ymm:
		xorps xmm0, xmm0 ; Clears YMM0's upper half too
		jmp SHORT ymm_copy_setup
	c_is_not_zero_ymm:
		mov rcx, fill_const
		movzx r11, r10b
		imul rcx, r11
		movq xmm0, r11
		movlhps xmm0, xmm0
		vpbroadcastb ymm0, xmm0
		jmp SHORT ymm_copy_setup

	; Copy xmmwords. R11 is the current address, RDX is the end address
	xmm_copy_setup:
		mov r11, r12
		add r11, i
		mov rdx, r12
		add rdx, r8
	xmm_copy:
		; Check exit condition
		cmp r11, rdx
		jae SHORT xmm_copy_end

		; Copy
		movdqu XMMWORD PTR [r11], xmm0

		; Increase the pointer
		add r11, 16
		jmp SHORT xmm_copy
	xmm_copy_end:

	; Copy ymmwords. Same as xmm_copy
	ymm_copy_setup:
		mov r11, r12
		add r11, i
		mov rdx, r12
		add rdx, r8
	ymm_copy:
		; Check exit condition
		cmp r11, rdx
		jae SHORT ymm_copy_end

		; Copy
		vmovdqu YMMWORD PTR [r11], ymm0

		; Increase the pointer
		add r11, 32
		jmp SHORT ymm_copy
	ymm_copy_end:

	; Return
	return:
		mov rax, r12 ; Most string.h functions return the destination pointer
		pop r13
		pop r12
		pop rcx
		leave
		ret
memset ENDP
PUBLIC memset

END
