;  Linux version of memset
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

BITS 64
DEFAULT REL

; Detected CPU features
EXTERN __features:__cpu_features

SECTION .rodata

; Constant to fill a qword
fill_const dq 0101010101010101h

SECTION .bss

%include "internal/nasm/asmdefs.S"

; Counter
i: resq 1

SECTION .text

GLOBAL memset
memset:
	; Stack setup
	push rbp
	mov rbp, rsp

	; Save RDX for DIV
	mov r8, rdx

	; Check for AVX and SSE
	mov rcx, __features
	mov dl, [rcx + avx]
	cmp dl, 1
	je ymm_setup
	mov dl, [rcx + sse]
	cmp dl, 1
	je xmm_setup
	jmp SHORT byte_copy ; Fast enough

	; Setup for the loops (R9 is the alignment, R11 is where to jump after alignment)
	ymm_setup:
		; See if it's viable to use AVX
		cmp r8, 32
		jle SHORT xmm_setup
		mov r9, 32 ; Align the address to 32 bytes
		mov rdx, ymm_fill_static_word

		jmp SHORT byte_align_copy_setup
	xmm_setup:
		cmp r8, 16
		jle SHORT byte_copy
		mov r9, 16 ; Align the address to 16 bytes
		mov r11, xmm_fill_static_word

		jmp byte_align_copy_setup
	byte_copy:
		; Check exit conditions
		cmp r8, QWORD [i]
		jae return

		; Copy the current byte
		mov r11, rdi
		add r11, QWORD [i]
		mov BYTE [r11], sil

		; Loop
		inc QWORD [rcx]
		jmp SHORT byte_copy
	; Return if execution is here
	jmp return

	; Align the pointer by copying individual bytes
	byte_align_copy_setup:
		cmp r8, 0
		je SHORT byte_align_copy_end
	byte_align_copy:
		; Check exit condition
		xor edx, edx
		mov rax, r8
		mov r11, r9
		div r11
		cmp r11, QWORD [i]
		jae return

		; Copy the value
		mov r11, rdi
		add r11, QWORD [i]
		mov BYTE [r11], sil

		; Increase the counter
		inc QWORD [i]
		jmp SHORT byte_align_copy
	byte_align_copy_end:

	; RDX has the label to set up for the main loop
	jmp rdx

	; Fill YMM0 with the value
	ymm_fill_static_word:
		cmp sil, 0
		je SHORT ymm_c_is_zero
		jmp SHORT ymm_c_is_not_zero
	ymm_c_is_zero:
		xorps xmm0, xmm0
		jmp ymm_copy_setup
	ymm_c_is_not_zero:
		mov rcx, QWORD [i]
		movzx r11, sil
		imul rcx, r11
		movq xmm0, r11
		movlhps xmm0, xmm0
		vpbroadcastb ymm0, xmm0
		jmp ymm_copy_setup

	; Fill XMM0 with the value
	xmm_fill_static_word:
		cmp sil, 0
		je SHORT xmm_c_is_zero
		jmp SHORT xmm_c_is_not_zero
	xmm_c_is_zero:
		xorps xmm0, xmm0
		jmp xmm_copy_setup
	xmm_c_is_not_zero:
		mov rcx, QWORD [i]
		movzx r11, sil
		imul rcx, r11
		movq xmm0, r11
		movlhps xmm0, xmm0
		jmp xmm_copy_setup

	; AVX copy. R11 is the current address, RDX is the end address
	ymm_copy_setup:
		mov r11, rdi
		add r11, QWORD [i]
		mov rdx, rdi
		add rdx, r8
	ymm_copy:
		; Check the exit condition
		cmp r11, rdx
		jae SHORT ymm_copy_end

		; Copy YMM0 to the destination
		vmovdqu YWORD [r11], ymm0

		; Increase the pointer
		add r11, 32
		jmp SHORT ymm_copy
	ymm_copy_end:

	; SSE copy. Same as the AVX one
	xmm_copy_setup:
		mov r11, rdi
		add r11, QWORD [i]
		mov rdx, rdi
		add rdx, r8
	xmm_copy:
		; Check the exit condition
		cmp r11, rdx
		jae SHORT xmm_copy_end

		; Copy XMM0
		movdqu OWORD [r11], xmm0

		; Increase the pointer
		add r11, 16
		jmp SHORT xmm_copy
	xmm_copy_end:

	; Return
	return:
		mov rax, rdi
		leave
		ret

