file(GLOB_RECURSE SOURCES source/**/*.h source/**/*.hpp source/**/*.c source/**/*.cpp)
add_library(neat_core SHARED ${SOURCES})

header_directories(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(neat_core PUBLIC ${HEADERS})

target_link_libraries(neat_core PUBLIC common)
target_link_libraries(neat_core PUBLIC -lstdc++fs)

header_directories(common_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
target_include_directories(neat_core PUBLIC ${common_HEADERS})


add_subdirectory(test)
