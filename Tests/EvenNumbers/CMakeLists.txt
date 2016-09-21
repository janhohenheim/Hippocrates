file(GLOB SOURCES Sources/Headers/*.h Sources/Implementations/*.cpp Sources/*.cpp ../TestingUtilities/Sources/Headers/*.h ../TestingUtilities/Sources/Implementations/*.cpp)

add_executable(Evenness ${SOURCES})
target_link_libraries(Evenness Hippocrates)

add_test(EvenNumbers ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Evenness)
