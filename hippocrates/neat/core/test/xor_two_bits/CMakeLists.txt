file(GLOB_RECURSE SOURCES *.cpp *.hpp)

add_executable(xor_two_bits ${SOURCES})
target_link_libraries(xor_two_bits Core)
target_link_libraries(xor_two_bits CoreTestingUtilities)

add_test(xor_two_bits ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xor_two_bits)
