cmake_minimum_required(VERSION 3.10)

set(LIBC_WIN32_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/internal/win32/defs.h
	${CMAKE_CURRENT_LIST_DIR}/include/internal/win32/ldr.h

	${CMAKE_CURRENT_LIST_DIR}/src/win32/crt0.c
	${CMAKE_CURRENT_LIST_DIR}/src/win32/ldr.c
	${CMAKE_CURRENT_LIST_DIR}/src/win32/rtc.c
)

set(LIBC_LINUX_X86_64_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/src/linux/x86_64/crt0.asm
)

set(LIBC_LINUX_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/src/linux/startup/init.c
)

if (${CMAKE_C_COMPILER_ARCHITECTURE_ID} MATCHES x64)
	set(LIBC_LINUX_SOURCES
		${LIBC_LINUX_X86_64_SOURCES}
		${LIBC_LINUX_SOURCES}
	)
endif()

set(LIBC_ALL_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/include/internal/crt0.h

	${CMAKE_CURRENT_LIST_DIR}/include/stdlib.h

	${CMAKE_CURRENT_LIST_DIR}/src/stdlib/search.c
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(LIBC_ALL_SOURCES ${LIBC_WIN32_SOURCES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(LIBC_ALL_SOURCES ${LIBC_LINUX_SOURCES})
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_library(shardc2 STATIC ${LIBC_ALL_SOURCES})
set_target_properties(shardc2 PROPERTIES LINKER_LANGUAGE C POSITION_INDEPENDANT_CODE ON)
