file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.cpp *.hpp)

add_executable(xor_three_bits ${SOURCES})
target_link_libraries(xor_three_bits Hippocrates)
target_include_directories(xor_three_bits PUBLIC ../TestingUtilities/Sources/Headers)

add_test(xor_three_bits ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xor_three_bits)
