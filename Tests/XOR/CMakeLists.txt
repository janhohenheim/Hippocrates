file(GLOB SOURCES Sources/Headers/*.h Sources/Implementations/*.cpp Sources/*.cpp)

add_executable(XOR_EXAMPLE ${SOURCES})
target_include_directories(XOR_EXAMPLE BEFORE PUBLIC ../TestingUtilities/Sources/Headers)

add_test(XOR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/XOR_EXAMPLE)
