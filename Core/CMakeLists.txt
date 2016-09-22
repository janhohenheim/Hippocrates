file(GLOB SOURCES Sources/Headers/*.h Sources/Implementations/*.cpp)
add_library(Core SHARED OBJECT ${SOURCES})
