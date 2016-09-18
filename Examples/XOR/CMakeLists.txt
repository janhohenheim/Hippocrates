file(GLOB SOURCES Sources/*.cpp Sources/*.h)

# TODO: Remove this and link the library
file(GLOB CORE_SOURCES ../../Core/Sources/*.cpp ../../Core/Sources/*.h)

add_executable(XOR_EXAMPLE ${SOURCES} ${CORE_SOURCES})

# TODO: Remove this when the library link is working
target_link_libraries(XOR_EXAMPLE -lstdc++fs)

add_test(XOR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/XOR_EXAMPLE)
