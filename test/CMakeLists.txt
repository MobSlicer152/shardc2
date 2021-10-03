cmake_minimum_required(VERSION 3.10)

set(TEST_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/src/test.c
)

add_executable(test ${TEST_SOURCES})
target_link_libraries(test shardc2)
