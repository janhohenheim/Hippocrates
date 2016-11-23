file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.cpp *.hpp)

add_executable(EvenNumbers ${SOURCES})
target_link_libraries(EvenNumbers Hippocrates)
target_include_directories(EvenNumbers PUBLIC ../TestingUtilities/Sources/Headers)

add_test(EvenNumbers ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EvenNumbers)
