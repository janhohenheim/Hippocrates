#include "max_pooler.hpp"
#include <algorithm>

using namespace Convolutional;
using namespace Convolutional::Layer::Pooler;

auto MaxPooler::ProcessMatrix(Matrix::Position position, const Matrix & matrix) const -> Matrix {
	Matrix featureMap{ matrix.GetSubmatrix(position, receptiveField) };
	Matrix::elementType highestValue = *std::max_element(featureMap.begin(), featureMap.end());

	for (auto& element : featureMap) {
		element = highestValue;
	}

	return featureMap;
}
