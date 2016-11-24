cmake_minimum_required(VERSION 3.2.2)
project(CNN)

if(APPLE)
    set(CMAKE_C_COMPILER /usr/local/bin/gcc)
    set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/tests)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.hpp *.cpp)
add_library(CNN SHARED ${SOURCES})

MACRO(HEADER_DIRECTORIES return_list sources_folder)
    FILE(GLOB_RECURSE headers [RELATIVE ${sources_folder}] *.hpp *.h)
    SET(dir_list "")
    FOREACH(file_path ${headers})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(HEADERS Sources)
target_include_directories(CNN PUBLIC ${HEADERS})

enable_testing()
add_subdirectory(Tests)
