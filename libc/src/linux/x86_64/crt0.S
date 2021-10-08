.section .text

// C-side initialization
.extern __libc_linux_init

.globl _start
_start:
	// Put argc and argv in the appropriate registers
	popq %rdi
	popq %rsi

	callq __libc_linux_init

