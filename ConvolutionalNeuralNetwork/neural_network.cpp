#include "neural_network.h"

using namespace Convolutional;

NeuralNetwork::NeuralNetwork(MultiDimensionalMatrix matrix):
	matrix(std::move(matrix))
{
}

auto NeuralNetwork::Pool(const IPooler& pooler) -> void {
    matrix = ApplyToAllDimensions([&pooler](Matrix::Position pos, const Matrix& matrix) {return pooler.Pool(pos, matrix);});
}

auto NeuralNetwork::Subsample(const Neuron & neuron) -> void {
    matrix = ApplyToAllDimensions([&neuron](Matrix::Position pos, const Matrix& matrix) {return neuron.ExtractFeature(pos, matrix); });
}