#include "layer/convolution.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto Convolution::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	std::vector<Matrix> matrices;
	matrices.reserve(convolution.size());
	for (auto & filter : convolution) {
		auto filteredMM = filter.ProcessMultiMatrix(multiMatrix);
		for (auto&& submatrix: filteredMM)
			matrices.push_back(std::move(submatrix));
	}
	return MultiMatrix { std::move(matrices) };
}