file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.cpp *.hpp)
add_library(Core SHARED OBJECT ${SOURCES})
