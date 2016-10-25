cmake_minimum_required(VERSION 3.2.2)
project(CNN_Code)

file(GLOB SOURCES ConvolutionalNeuralNetwork/*/*.cpp ConvolutionalNeuralNetwork/*/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(CNN_Code ${SOURCES})
