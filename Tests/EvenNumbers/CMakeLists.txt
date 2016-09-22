file(GLOB SOURCES Sources/Implementations/*.cpp)

add_executable(EvenNumbers_EXAMPLE ${SOURCES})
target_link_libraries(EvenNumbers_EXAMPLE Hippocrates)
target_include_directories(EvenNumbers_EXAMPLE PUBLIC ../TestingUtilities/Sources/Headers)

add_test(EvenNumbers ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EvenNumbers_EXAMPLE)
