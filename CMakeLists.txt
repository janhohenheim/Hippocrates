cmake_minimum_required(VERSION 3.2.2)
project(CNN_Code)

file(GLOB_RECURSE SOURCES [RELATIVE ConvolutionalNeuralNetwork] *.cpp *.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -std=gnu++1z")

add_executable(CNN_Code ${SOURCES})
