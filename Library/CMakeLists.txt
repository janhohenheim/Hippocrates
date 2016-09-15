file(GLOB SOURCES JNF_NEAT/*.cpp JNF_NEAT/*.h)
add_library(JNF_NEAT ${SOURCES})
target_link_libraries(JNF_NEAT -lstdc++fs)
