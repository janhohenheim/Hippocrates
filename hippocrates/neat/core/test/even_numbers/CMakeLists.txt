file(GLOB_RECURSE SOURCES *.cpp *.hpp)

add_executable(EvenNumbers ${SOURCES})
target_link_libraries(EvenNumbers Core)
target_link_libraries(EvenNumbers CoreTestingUtilities)

add_test(EvenNumbers ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EvenNumbers)
