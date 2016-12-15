#include "Layer/relu.hpp"
#include <algorithm>

using namespace Convolutional;
using namespace Convolutional::Layer;

auto ReLU::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	auto rectifiedMultiMatrix = multiMatrix;
	for (auto& matrix : rectifiedMultiMatrix)
		for (auto& element : matrix)
			element = std::max(static_cast<Matrix::element_t>(0), element);
	return rectifiedMultiMatrix;
}
