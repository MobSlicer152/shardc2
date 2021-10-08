BITS 64
DEFAULT REL

SECTION .text

; Get the results from CPUID with the given RAX and RCX values
GLOBAL __cpuid
__cpuid:
	
