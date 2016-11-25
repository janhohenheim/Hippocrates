#include <algorithm>
#include "Layer/Pooler/max_pooler.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer::Pooler;

auto MaxPooler::ProcessMatrix(Matrix::Position position, const Matrix & matrix) const -> Matrix {
	Matrix featureMap{ matrix.GetSubmatrix(position, receptiveField) };
	Matrix::element_t highestValue = *std::max_element(featureMap.begin(), featureMap.end());

	for (auto& element : featureMap) {
		element = highestValue;
	}

	return featureMap;
}
