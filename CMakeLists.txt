cmake_minimum_required(VERSION 3.2.2)
project(Hippocrates)

if(APPLE)
	set(CMAKE_C_COMPILER /usr/local/bin/gcc)
	set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/tests)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(CMAKE_C_FLAGS -fPIC)
set(CMAKE_CXX_FLAGS -fPIC)

add_subdirectory(Core)

add_library(Hippocrates SHARED $<TARGET_OBJECTS:Core>)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(Hippocrates -lstdc++fs)
target_link_libraries(Hippocrates Threads::Threads)

enable_testing()
add_subdirectory(Tests)
