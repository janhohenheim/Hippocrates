#include <cmath>
#include <stdexcept>

#include "Layer/filter.hpp"
#include "Utility/utility.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

Filter::Filter(std::size_t size) :
bias{Utility::GetRandomNumberBetween(-1.0, 1.0)} {
	// TODO jnf: constexpr check if size is perfect square
	weights.reserve(size);
	for (size_t i = 0; i < size; ++i) {
		weights.push_back(Utility::GetRandomNumberBetween(-1.0, 1.0));
	}
}


auto Filter::ProcessMatrix(Matrix matrix) const -> Matrix {
	if (matrix.GetElementCount() != weights.size()) {
		throw std::invalid_argument("Number of weights in filter does not match number of elements in matrix");
	}

	auto featureValue = bias;
	auto weight = weights.begin();
	for (const auto& element : matrix) {
		featureValue += element * *weight;
		++weight;
	}
	featureValue = sigmoid(featureValue);

	for (auto& element : matrix) {
		element = featureValue;
	}

	return matrix;
}

auto Filter::sigmoid(Matrix::element_t n) -> double {
	return tanh(n);
}

