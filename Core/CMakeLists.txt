file(GLOB_RECURSE SOURCES [RELATIVE Sources] *.cpp *.hpp *.c *.h)
add_library(Core SHARED OBJECT ${SOURCES})
