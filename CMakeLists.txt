cmake_minimum_required(VERSION 3.2.2)
project(CNN_Code)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -std=gnu++1z")

file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.hpp *.cpp)
add_executable(CNN_Code ${SOURCES})

file(GLOB files Sources/Headers Sources/Headers/**)
foreach(element ${files})
    if(IS_DIRECTORY ${element})
        target_include_directories(CNN_Code PRIVATE ${element})
    endif()
endforeach()
