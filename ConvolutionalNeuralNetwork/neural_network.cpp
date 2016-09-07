#include "neural_network.h"

using namespace Convolutional;

NeuralNetwork::NeuralNetwork(MultiDimensionalMatrix matrix):
	matrix(std::move(matrix))
{
}

auto NeuralNetwork::Pool(const IPooler& pooler) -> void {
	ApplyToAllMatrices(pooler.Pool);
}

auto NeuralNetwork::Subsample(const Neuron & neuron) -> void {
	ApplyToAllMatrices(neuron.ExtractFeature);
}

auto NeuralNetwork::ApplyToAllMatrices(std::function<Matrix(const Matrix&)> function) -> void {
	MultiDimensionalMatrix::SubDimensionType featureDimensions;
	featureDimensions.reserve(matrix.GetDimensionCount());
	for (auto & submatrix : matrix) {
		auto processedMatrix = function(submatrix);
		featureDimensions.push_back(std::move(processedMatrix));
	}
	MultiDimensionalMatrix feature(std::move(featureDimensions));
}