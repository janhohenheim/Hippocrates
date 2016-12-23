file(GLOB_RECURSE SOURCES *.h *.hpp *.c *.cpp)
add_library(common SHARED ${SOURCES})

header_directories(HEADERS ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(common PUBLIC ${HEADERS})
