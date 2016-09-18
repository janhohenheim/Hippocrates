file(GLOB SOURCES Sources/*.cpp Sources/*.h)

add_executable(XOR_EXAMPLE ${SOURCES})
target_link_libraries(XOR_EXAMPLE JNF_NEAT)

add_test(XOR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/XOR_EXAMPLE)
