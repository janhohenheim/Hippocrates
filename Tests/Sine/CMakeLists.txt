file(GLOB SOURCES Sources/Headers/*.h Sources/Implementations/*.cpp)

add_executable(Sine_EXAMPLE ${SOURCES})
target_link_libraries(Sine_EXAMPLE Hippocrates)
target_include_directories(Sine_EXAMPLE PUBLIC ../TestingUtilities/Sources/Headers)

add_test(Sine ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sine_EXAMPLE)
set_tests_properties(Sine PROPERTIES TIMEOUT 1200)
