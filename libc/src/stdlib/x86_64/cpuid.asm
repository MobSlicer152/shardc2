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

