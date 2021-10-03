cmake_minimum_required(VERSION 3.10)

# Disables default libraries on Windows, since my code loads them dynamically
file(
    WRITE "${CMAKE_BINARY_DIR}/no_system_import_libs.cmake"
[=[
if (MSVC)        
    set(CMAKE_CXX_STANDARD_LIBRARIES_INIT "%(AdditionalDependencies)")
endif()
]=]
)
set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_BINARY_DIR}/no_system_import_libs.cmake")

project(shardc2 VERSION 0.0.1 LANGUAGES C ASM_NASM)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

option(SHARDC2_BUILD_TEST "Whether to build the test program" ON)

set(CMAKE_C_STANDARD 17)

if (MSVC)
	# Basically kill any reference to the CRT and enable C17 support, plus disable warnings from API headers
	set(CMAKE_C_FLAGS "/Wall /Zl /Zo /std:c17 /wd4115 /wd4255 /wd4324 /wd4668 /wd4820")
else()
	set(CMAKE_C_FLAGS "-Wall -Wextra")
	set(CMAKE_EXE_LINKER_FLAGS "-nostdlib")
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/deps/include)

message(STATUS "CFLAGS: ${CMAKE_C_FLAGS}")

add_subdirectory(libc)

if (${SHARDC2_BUILD_TEST})
	add_subdirectory(test)
endif()

