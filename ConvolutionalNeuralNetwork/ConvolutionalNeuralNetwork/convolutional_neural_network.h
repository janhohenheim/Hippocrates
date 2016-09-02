#pragma once
#include <memory>
#include "iconvolutional_matrix.h"

class ConvolutionalNeuralNetwork {
public:
    ConvolutionalNeuralNetwork(std::unique_ptr<IConvolutionalMatrix> matrix);

private:
    std::unique_ptr<IConvolutionalMatrix> matrix;
};