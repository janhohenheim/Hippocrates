file(GLOB SOURCES Sources/Headers/*.hpp Sources/Implementations/*.cpp)
add_library(Core SHARED OBJECT ${SOURCES})
