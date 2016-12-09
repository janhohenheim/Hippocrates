#include "Layer/filters.hpp"
using namespace Convolutional::Layer;

auto Filters::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	std::vector<Matrix> matrices;
	matrices.reserve(filters.size());
	for (auto & filter : filters) {
		auto filteredMM = filter.ProcessMultiMatrix(multiMatrix);
		for (auto&& submatrix: filteredMM)
			matrices.push_back(std::move(submatrix));
	}
	return MultiMatrix { std::move(matrices) };
}