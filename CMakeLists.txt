cmake_minimum_required(VERSION 3.2.2)
project(CNN_Code)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -std=gnu++1z")

file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.hpp *.cpp)
add_executable(CNN_Code ${SOURCES})

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE headers [RELATIVE Sources] *.hpp)
    SET(dir_list "")
    FOREACH(file_path ${headers})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(HEADERS)
target_include_directories(CNN_Code PRIVATE ${HEADERS})
