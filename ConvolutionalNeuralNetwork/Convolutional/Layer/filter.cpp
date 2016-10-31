#include "filter.hpp"
#include <cmath>
#include <stdexcept>

using namespace Convolutional;
using namespace Layer;

auto Filter::ProcessMatrix(Matrix::Position position, const Matrix& matrix) const -> Matrix {
	if (matrix.GetElementCount() != weights.size()) {
		throw std::invalid_argument("Number of weights in filter does not match number of elements in matrix");
	}

	Matrix featureMap{matrix.GetSubmatrix(position, receptiveField)};

	Matrix::elementType featureValue = bias;
	auto weight = weights.begin();
	for (const auto& element : featureMap) {
		featureValue += element + *weight;
		++weight;
	}
	featureValue = sigmoid(featureValue);

	for (auto& element : featureMap) {
		element = featureValue;
	}

	return featureMap;
}

auto Filter::sigmoid(Matrix::elementType n) -> double {
	return tanh(n);
}
