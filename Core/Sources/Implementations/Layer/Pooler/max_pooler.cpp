#include <algorithm>
#include "Layer/Pooler/max_pooler.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer::Pooler;

auto MaxPooler::ProcessMatrix(Matrix matrix) const -> Matrix {
	Matrix::element_t highestValue = *std::max_element(matrix.begin(), matrix.end());

	for (auto& element : matrix) {
		element = highestValue;
	}

	return matrix;
}
