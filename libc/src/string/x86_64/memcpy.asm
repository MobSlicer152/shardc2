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

.const

.data
INCLUDE internal/win32/asmdefs.asm

; Detected features from mainCRTStartup
EXTERN __features:__cpu_features

; Counter
i DQ 0

.code

memcpy PROC
	; Stack setup
	push rbp
	mov rbp, rsp

	; Save RCX and RDX
	mov r10, rcx
	mov r11, rdx

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

memcpy ENDP
PUBLIC memcpy

END
