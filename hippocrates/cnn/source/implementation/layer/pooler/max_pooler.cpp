#include <algorithm>
#include "layer/pooler/max_pooler.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer::Pooler;

auto MaxPooler::ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix {
	MultiMatrix::dimensions_t dimensions;
	dimensions.reserve(multiMatrix.GetDimensionCount());
	for (auto& submatrix : multiMatrix) {
		const auto size = submatrix.GetSize();
		const auto receptiveField = GetReceptiveField(size);
		const auto stride = GetStride(size);
		Matrix pooledMatrix(GetDimensionalityAfterProcessing(multiMatrix.GetDimensionality()).size);
		auto currPooledElement = pooledMatrix.begin();
		Matrix::Position pos;
		for (pos.y = 0; pos.y < size.height - receptiveField.height; pos.y += stride.height) {
			for (pos.x = 0; pos.x < size.width - receptiveField.width; pos.x += stride.width) {
				auto receptedMatrix = submatrix.GetSubmatrix(pos, receptiveField);
				*currPooledElement = ProcessSubmatrix(std::move(receptedMatrix));
				++currPooledElement;
			}
		}
		dimensions.emplace_back(std::move(pooledMatrix));
	}
	return MultiMatrix(dimensions);
}

auto MaxPooler::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	const auto size = dimensionality.size;
	const auto r = GetReceptiveField(size);
	const auto s = GetStride(size);

	MultiMatrix::Dimensionality newDim;
	newDim.size.height = (size.width - r.width) / s.width + 1;
	newDim.size.width = (size.height - r.height) / s.height + 1;
	newDim.dimensionCount = dimensionality.dimensionCount;
	return newDim;
}

auto MaxPooler::ProcessSubmatrix(const MatrixView& matrix) const -> Matrix::element_t {
	auto maxElement{matrix.ElementAt(0)};
	for (std::size_t i = 0; i < matrix.GetElementCount(); ++i) {
		maxElement = std::max(maxElement, matrix.ElementAt(i));
	}
	return maxElement;
}
