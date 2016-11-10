file(GLOB SOURCES Sources/Headers/*.hpp Sources/Headers/*.h Sources/Implementations/*.cpp Sources/Implementations/*.c)
add_library(Core SHARED OBJECT ${SOURCES})
