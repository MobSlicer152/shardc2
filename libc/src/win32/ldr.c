#include "internal/win32/defs.h"

#include <stdint.h>

// Base addresses of important DLLs
uint8_t *__ntdll;
uint8_t *__kernel32;

void __load_lib_dep_funcs(PEB *peb)
{
	PEB_LDR_DATA *ldr;
	LIST_ENTRY *head;
	LIST_ENTRY *cur;
	LDR_DATA_TABLE_ENTRY *cur_dll;

	// Search for the loader data for NTDLL
	ldr = peb->Ldr;
	head = &ldr->InMemoryOrderModuleList;
	for (cur = head; cur != head; cur = cur->Flink) {
		cur_dll = CONTAINING_RECORD(cur, LDR_DATA_TABLE_ENTRY,
					    InMemoryOrderLinks);
		
	}
}
