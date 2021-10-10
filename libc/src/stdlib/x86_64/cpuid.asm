.code

_cpuid PROC
	push rbp
	mov rbp, rsp
	push rbx ; RBX is non-volatile

	; Place parameters in the right registers
	mov rax, rcx
	mov rcx, rdx

	; Call cpuid
	cpuid

	; Pop the last two parameters
	pop r10
	pop r11

	; Move the results into the pointers
	mov QWORD PTR [r8], rax
	mov QWORD PTR [r9], rbx
	mov QWORD PTR [r10], rdx
	mov QWORD PTR [r11], rcx

	pop rbx
	pop rbp
	ret
_cpuid ENDP
PUBLIC _cpuid

END

