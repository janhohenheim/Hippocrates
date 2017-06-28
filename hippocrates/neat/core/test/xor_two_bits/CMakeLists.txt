file(GLOB_RECURSE SOURCES *.cpp *.hpp)

add_executable(xor_two_bits ${SOURCES})
target_link_libraries(xor_two_bits neat_core)
target_link_libraries(xor_two_bits neat_core_testingutilities)

header_directories(neat_core_testingutilities_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../testing_utilities/source)
target_include_directories(xor_two_bits PUBLIC ${neat_core_testingutilities_HEADERS})

add_test(xor_two_bits ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xor_two_bits)
