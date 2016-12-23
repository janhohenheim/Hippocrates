file(GLOB_RECURSE SOURCES *.cpp *.hpp)

add_executable(sandbox ${SOURCES})
target_link_libraries(sandbox cnn)

add_test(sandbox ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sandbox)
