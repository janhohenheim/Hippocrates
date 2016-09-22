file(GLOB SOURCES Sources/Implementations/*.cpp)

add_executable(XOR_EXAMPLE ${SOURCES})
target_link_libraries(XOR_EXAMPLE Hippocrates)
target_include_directories(XOR_EXAMPLE PUBLIC ../TestingUtilities/Sources/Headers)

add_test(XOR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/XOR_EXAMPLE)
set_tests_properties(XOR PROPERTIES TIMEOUT 1200)
