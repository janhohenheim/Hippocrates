file(GLOB_RECURSE SOURCES *.cpp *.hpp)

add_executable(even_numbers ${SOURCES})
target_link_libraries(even_numbers neat_core)
target_link_libraries(even_numbers neat_core_testingutilities)

header_directories(neat_core_testingutilities_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../testing_utilities/source)
target_include_directories(even_numbers PUBLIC ${neat_core_testingutilities_HEADERS})

add_test(even_numbers ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/even_numbers)
