cmake_minimum_required(VERSION 3.2.2)
project(JNF_NEAT)

if(APPLE)
	SET(CMAKE_C_COMPILER /usr/local/bin/gcc)
	SET(CMAKE_CXX_COMPILER /usr/local/bin/g++)
endif()

file(GLOB JNF_NEAT_SOURCES JNF_NEAT/*.cpp JNF_NEAT/*.h)
file(GLOB EXAMPLE_SOURCES Examples/Examples/*.cpp Examples/Examples/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(JNF_NEAT ${JNF_NEAT_SOURCES} ${EXAMPLE_SOURCES})
target_link_libraries(JNF_NEAT -lstdc++fs)
