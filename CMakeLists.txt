cmake_minimum_required(VERSION 3.2.2)
project(JNF_NEAT)

if(APPLE)
	set(CMAKE_C_COMPILER /usr/local/bin/gcc)
	set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/examples)

set(CMAKE_CXX_FLAGS -fPIC)

add_subdirectory(Core)

add_library(JNF_NEAT SHARED $<TARGET_OBJECTS:Core>)
target_link_libraries(JNF_NEAT -lstdc++fs)

enable_testing()
add_subdirectory(Examples)
