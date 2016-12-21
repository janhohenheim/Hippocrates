file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.cpp *.hpp)

add_executable(Sandbox ${SOURCES})
target_link_libraries(Sandbox CNN)

add_test(Sandbox ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Sandbox)
