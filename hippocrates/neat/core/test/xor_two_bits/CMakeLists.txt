file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.cpp *.hpp)

add_executable(xor_two_bits ${SOURCES})
target_link_libraries(xor_two_bits Hippocrates)
target_include_directories(xor_two_bits PUBLIC ../TestingUtilities/Sources/Headers)

add_test(xor_two_bits ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xor_two_bits)
