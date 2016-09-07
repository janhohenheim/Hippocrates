cmake_minimum_required(VERSION 3.5)
project(CNN_Code)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    ConvolutionalNeuralNetwork/ipooler.h
    ConvolutionalNeuralNetwork/matrix.cpp
    ConvolutionalNeuralNetwork/matrix.h
    ConvolutionalNeuralNetwork/multi_dimensional_matrix.cpp
    ConvolutionalNeuralNetwork/multi_dimensional_matrix.h
    ConvolutionalNeuralNetwork/multi_dimensional_matrix_parser.cpp
    ConvolutionalNeuralNetwork/multi_dimensional_matrix_parser.h
    ConvolutionalNeuralNetwork/neural_network.cpp
    ConvolutionalNeuralNetwork/neural_network.h
    ConvolutionalNeuralNetwork/neural_network_trainer.cpp
    ConvolutionalNeuralNetwork/neural_network_trainer.h
    ConvolutionalNeuralNetwork/neuron.cpp
    ConvolutionalNeuralNetwork/neuron.h
    ConvolutionalNeuralNetwork/training_data.h
    ConvolutionalNeuralNetwork/main.cpp)

add_executable(CNN_Code ${SOURCE_FILES})