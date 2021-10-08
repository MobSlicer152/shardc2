.section .text

.global __cpuid
.type __cpuid, @function
__cpuid:
	pushq %rbp
	movq %rsp, %rbp
	pushq %rbx

	// Back up the parameters in RCX and RDX
	pushq %rdx
	pushq %rcx

	// Put the values desired for RAX and RCX in the right places
	movq %rdi, %rax
	movq %rsi, %rcx

	// Call cpuid
	cpuid

	// Move the results into the pointers given
	popq %r11
	movq %rax, (%r11)
	popq %r11
	movq %rbx, (%r11)
	movq %rcx, (%r8)
	movq %rdx, (%r9)

	popq %rbx
	popq %rbp
	ret

