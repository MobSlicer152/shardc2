BITS 64
DEFAULT REL

; C initialization
EXTERN __libc_linux_init

; Setup code
GLOBAL _start
_start:
	; The program loader sticks the arguments on the stack
	pop rdi ; argc
	pop rsi ; argv

	; Jump into the main initialization function
	call __libc_linux_init


