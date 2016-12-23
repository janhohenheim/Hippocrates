cmake_minimum_required(VERSION 2.8)
project(Hippocrates)

set(CMAKE_BUILD_TYPE Release)

include(hippocrates/CMakeLists.macros)
set(CMAKE_MACOSX_RPATH 1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/tests)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

add_subdirectory(hippocrates/common)
add_subdirectory(hippocrates/cnn)
add_subdirectory(hippocrates/neat)
