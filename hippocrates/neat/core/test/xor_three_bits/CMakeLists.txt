file(GLOB_RECURSE SOURCES *.cpp *.hpp)

add_executable(xor_three_bits ${SOURCES})
target_link_libraries(xor_three_bits neat_core)
target_link_libraries(xor_three_bits neat_core_testingutilities)

header_directories(neat_core_testingutilities_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../testing_utilities/source)
target_include_directories(xor_three_bits PUBLIC ${neat_core_testingutilities_HEADERS})

add_test(xor_three_bits ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/xor_three_bits)
