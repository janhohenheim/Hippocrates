#include <algorithm>
#include <numeric>
#include "layer/pooler/global_average_pooler.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer::Pooler;

auto GlobalAveragePooler::ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix {
	const auto dimensions = multiMatrix.GetDimensionCount();
	Matrix averages{{dimensions, 0}};
	for (std::size_t i = 0; i < dimensions; ++i) {
		averages.ElementAt({i,0}) = ProcessMatrix(*(multiMatrix.begin() + i));
	}
	return MultiMatrix {{averages}};
}

auto GlobalAveragePooler::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	MultiMatrix::Dimensionality newDim;
	newDim.size.height = 1;
	newDim.size.width = dimensionality.dimensionCount;
	newDim.dimensionCount = 1;
	return newDim;
}

auto GlobalAveragePooler::ProcessMatrix(const Matrix& matrix) const -> Matrix::element_t {
	const auto total = std::accumulate(matrix.begin(), matrix.end(), static_cast<Matrix::element_t>(0));
	const auto amount = static_cast<Matrix::element_t>(matrix.GetElementCount());
	return total / amount;
}