#include <cmath>
#include <stdexcept>
#include <vector>

#include "Layer/filter.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;




auto Filter::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	LazyInitializeWeights(multiMatrix.GetSize(), multiMatrix.GetDimensionCount());
	/*
	if (matrix.GetElementCount() != weights->GetElementCount()) {
		throw std::invalid_argument("Number of weights in filter does not match number of elements in matrix");
	}

	auto featureValue = bias;
	auto weight = weights->begin();
	for (const auto& element : matrix) {
		featureValue += element * (*weight);
		++weight;
	}
	featureValue = sigmoid(featureValue);

	for (auto& element : matrix) {
		element = featureValue;
	}

	return matrix;
	*/
	return multiMatrix;
}

auto Filter::GetWeights() const -> const MultiMatrix& {
	if (!weights) 
		throw std::runtime_error("Weights have not been initialized yet! Call ProcessMultiMatrix first"); 
	return *weights;
}

auto Filter::LazyInitializeWeights(Matrix::Size size, std::size_t dimensionCount) -> void {
	if (weights) {
		return;
	}

	// TODO jnf: constexpr check if size is perfect square
	std::vector<Matrix> matrices;
	matrices.reserve(dimensionCount);
	for (std::size_t i = 0; i < dimensionCount; ++i) {
		Matrix matrix {size};
		for (auto& element : matrix) {
			element = Utility::GetRandomNumberBetween(-1.0, 1.0);
		}
		matrices.push_back(std::move(matrix));
	}
	weights = std::make_unique<MultiMatrix>(std::move(matrices));
}

auto Filter::sigmoid(Matrix::element_t n) -> double {
	return tanh(n);
}

