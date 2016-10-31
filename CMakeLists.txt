cmake_minimum_required(VERSION 3.2.2)
project(CNN_Code)

file(GLOB SOURCES ConvolutionalNeuralNetwork/main.cpp
		ConvolutionalNeuralNetwork/Convolutional/*.cpp
		ConvolutionalNeuralNetwork/Convolutional/*.hpp
		ConvolutionalNeuralNetwork/Convolutional/InputData/*.cpp
		ConvolutionalNeuralNetwork/Convolutional/InputData/*.hpp
		ConvolutionalNeuralNetwork/Convolutional/Layer/*.cpp
		ConvolutionalNeuralNetwork/Convolutional/Layer/*.hpp
		ConvolutionalNeuralNetwork/Convolutional/Layer/Pooler/*.cpp
		ConvolutionalNeuralNetwork/Convolutional/Layer/Pooler/*.hpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -std=gnu++1z")

add_executable(CNN_Code ${SOURCES})
