cmake_minimum_required(VERSION 2.8)
project(CNN)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/tests)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(CMAKE_C_FLAGS -fPIC)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++1z")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

add_subdirectory(Core)
add_library(CNN SHARED $<TARGET_OBJECTS:Core>)

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
target_link_libraries(CNN PUBLIC ${ImageMagick_LIBRARIES})
target_include_directories(Core PRIVATE ${ImageMagick_INCLUDE_DIRS})
target_include_directories(CNN PUBLIC ${ImageMagick_INCLUDE_DIRS})

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

HEADER_DIRECTORIES(HEADERS Core/Sources)
target_include_directories(CNN PUBLIC ${HEADERS})

enable_testing()
add_subdirectory(Tests)

