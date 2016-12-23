file(GLOB_RECURSE SOURCES *.cpp *.hpp *.c *.h)
add_library(neat_core_testingutilities SHARED ${SOURCES})

header_directories(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/source/header)
target_include_directories(neat_core_testingutilities PUBLIC ${HEADERS})
