cmake_minimum_required(VERSION 2.8)
project(Hippocrates)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/tests)

add_subdirectory(hippocrates/common)
add_subdirectory(hippocrates/cnn)
add_subdirectory(hippocrates/neat)

#cmake_minimum_required(VERSION 2.8)
#project(Hippocrates)
#
#set(CMAKE_BUILD_TYPE Release)
#
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/tests)
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
#
#set(CMAKE_C_FLAGS -fPIC)
#set(CMAKE_CXX_FLAGS "-fPIC -std=c++1z")
#
#if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
#    set(CMAKE_SHARED_LINKER_FLAGS -lc++experimental)
#endif()
#
#add_subdirectory(Core)
#add_library(Hippocrates SHARED $<TARGET_OBJECTS:Core>)
#
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#
#target_link_libraries(Hippocrates -lstdc++fs)
#target_link_libraries(Hippocrates Threads::Threads)
#
#MACRO(HEADER_DIRECTORIES return_list sources_folder)
#	FILE(GLOB_RECURSE headers [RELATIVE ${sources_folder}] *.hpp *.h)
#	SET(dir_list "")
#	FOREACH(file_path ${headers})
#		GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
#		SET(dir_list ${dir_list} ${dir_path})
#	ENDFOREACH()
#	LIST(REMOVE_DUPLICATES dir_list)
#	SET(${return_list} ${dir_list})
#ENDMACRO()
#
#HEADER_DIRECTORIES(HEADERS Core/Sources)
#target_include_directories(Hippocrates PUBLIC ${HEADERS})
#
#enable_testing()
#add_subdirectory(Tests)
#

#[[
cmake_minimum_required(VERSION 2.8)
project(NEAT)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/tests)

set(CMAKE_C_FLAGS -fPIC)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++1z")

add_subdirectory(core)
add_library(NEAT SHARED $<TARGET_OBJECTS:Core>)
]]

#[[
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(NEAT -lstdc++fs)
target_link_libraries(NEAT Threads::Threads)

macro(header_directories return_list sources_folder)
	file(GLOB_RECURSE headers [RELATIVE ${sources_folder}] *.hpp *.h)
	set(dir_list "")
	foreach(file_path ${headers})
		get_filename_component(dir_path ${file_path} PATH)
		set(dir_list ${dir_list} ${dir_path})
	endforeach()
	list(REMOVE_DUPLICATES dir_list)
	set(${return_list} ${dir_list})
endmacro()

header_directories(HEADERS core/sources/headers)
target_include_directories(NEAT PUBLIC ${HEADERS})
]]
