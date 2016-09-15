cmake_minimum_required(VERSION 3.2.2)
project(Library)

if(APPLE)
	set(CMAKE_C_COMPILER /usr/local/bin/gcc)
	set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
endif()

add_subdirectory(Library)
add_subdirectory(Examples)
