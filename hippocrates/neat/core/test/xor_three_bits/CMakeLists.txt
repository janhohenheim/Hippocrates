file(GLOB_RECURSE SOURCES *.cpp *.hpp)

add_executable(xor_three_bits ${SOURCES})
target_link_libraries(xor_three_bits Core)
target_link_libraries(xor_three_bits CoreTestingUtilities)

add_test(xor_three_bits ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xor_three_bits)
