file(GLOB_RECURSE SOURCES source/**/*.h source/**/*.hpp source/**/*.c source/**/*.cpp)
add_library(cnn SHARED ${SOURCES})

header_directories(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/source)
target_include_directories(cnn PUBLIC ${HEADERS})

target_link_libraries(cnn PUBLIC common)

header_directories(common_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../common)
MESSAGE("${common_HEADERS}")
target_include_directories(cnn PUBLIC ${common_HEADERS})

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)
target_link_libraries(cnn PUBLIC ${ImageMagick_LIBRARIES})
target_include_directories(cnn PUBLIC ${ImageMagick_INCLUDE_DIRS})
