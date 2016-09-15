file(GLOB SOURCES Examples/*.cpp Examples/*.h)
add_executable(JNF_NEAT_EXAMPLES ${SOURCES})
target_link_libraries(JNF_NEAT_EXAMPLES JNF_NEAT)
