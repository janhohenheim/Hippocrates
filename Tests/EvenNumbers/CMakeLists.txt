file(GLOB SOURCES Sources/Headers/*.h Sources/Implementations/*.cpp Sources/*.cpp ../TestingUtilities/Sources/Headers/*.h ../TestingUtilities/Sources/Implementations/*.cpp)

add_executable(EvenNumbers ${SOURCES})

add_test(EvenNumbers ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EvenNumbers)
