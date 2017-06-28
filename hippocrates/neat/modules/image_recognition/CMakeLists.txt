file(GLOB_RECURSE SOURCES source/**/*.h source/**/*.hpp source/**/*.c source/**/*.cpp)
add_library(image_recognition SHARED ${SOURCES})

header_directories(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(image_recognition PUBLIC ${HEADERS})

target_link_libraries(image_recognition PUBLIC cnn)
target_link_libraries(image_recognition PUBLIC neat_core)

header_directories(neat_core_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../../core/source)
target_include_directories(image_recognition PUBLIC ${neat_core_HEADERS})


add_subdirectory(test)
