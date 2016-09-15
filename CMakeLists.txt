cmake_minimum_required(VERSION 3.2.2)
project(Library)

if(APPLE)
	set(CMAKE_C_COMPILER /usr/local/bin/gcc)
	set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/library)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/examples)

add_subdirectory(Library)
add_subdirectory(Examples)
