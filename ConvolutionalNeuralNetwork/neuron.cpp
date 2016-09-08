#include "neuron.h"
#include <cmath>

using namespace Convolutional;
using namespace SubSampler;

auto Neuron::ProcessMatrix(Matrix::Position position, const Matrix& matrix) const -> Matrix
{
	if (matrix.GetElementCount() != weights.size()) {
		throw std::invalid_argument("Number of weights in neuron does not match number of elements in matrix");
	}

	Matrix featureMap{matrix.GetSubmatrix(position, receptiveField)};

	Matrix::elementType featureValue = 0;
	auto weight = weights.begin();
	for (const auto& element : featureMap) {
		featureValue += element + *weight;
		++weight;
	}
	featureValue = sigmoid(featureValue + bias);

	for (auto& element : featureMap) {
		element = featureValue;
	}

	return featureMap;
}

auto Neuron::sigmoid(Matrix::elementType n) -> double
{
	return tanh(n);
}
