file(GLOB SOURCES Sources/Headers/*.h Sources/Implementations/*.cpp Sources/*.cpp ../TestingUtilities/Sources/Headers/*.h ../TestingUtilities/Sources/Implementations/*.cpp)

add_executable(XOR_EXAMPLE ${SOURCES})
target_link_libraries(XOR_EXAMPLE JNF_NEAT)

add_test(XOR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/XOR_EXAMPLE)
