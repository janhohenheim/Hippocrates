file(GLOB_RECURSE SOURCES source/**/*.h source/**/*.hpp source/**/*.c source/**/*.cpp)
add_library(neat_core SHARED ${SOURCES})

header_directories(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(neat_core PUBLIC ${HEADERS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(neat_core PUBLIC common)
target_link_libraries(neat_core PUBLIC -lstdc++fs)
target_link_libraries(neat_core PUBLIC Threads::Threads)

header_directories(common_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
target_include_directories(neat_core PUBLIC ${common_HEADERS})


add_subdirectory(test)
