file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.cpp *.hpp)

add_executable(XOR_EXAMPLE ${SOURCES})
target_link_libraries(XOR_EXAMPLE Hippocrates)
target_include_directories(XOR_EXAMPLE PUBLIC ../TestingUtilities/Sources/Headers)

add_test(XOR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/XOR_EXAMPLE)
