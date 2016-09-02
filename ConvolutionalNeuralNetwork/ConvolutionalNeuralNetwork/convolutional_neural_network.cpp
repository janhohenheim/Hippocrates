#include "convolutional_neural_network.h"

ConvolutionalNeuralNetwork::ConvolutionalNeuralNetwork(std::unique_ptr<IConvolutionalMatrix> matrix):
    matrix(std::move(matrix))
{
}
