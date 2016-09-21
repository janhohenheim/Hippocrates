file(GLOB SOURCES Sources/Headers/*.h Sources/Implementations/*.cpp Sources/*.cpp)

add_executable(EvenNumbers ${SOURCES})
target_include_directories(EvenNumbers BEFORE PUBLIC ../TestingUtilities/Sources/Headers)

add_test(EvenNumbers ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EvenNumbers)
