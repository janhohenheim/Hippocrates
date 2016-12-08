#include <algorithm>
#include "Layer/Pooler/max_pooler.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer::Pooler;

auto MaxPooler::ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix {
	MultiMatrix::dimensions_t dimensions;
	dimensions.reserve(multiMatrix.GetDimensionCount());
	for (auto& submatrix : multiMatrix) {
		Matrix::Position pos;
		const auto size = submatrix.GetSize();
		const auto receptiveField = GetReceptiveField(size);
		const auto stride = GetStride(size);
		Matrix pooledMatrix(GetSizeAfterPooling(size));
		auto currPooledElement = pooledMatrix.begin();
		for (; pos.y < size.height - receptiveField.height; pos.y += stride.height) {
			for (; pos.x < size.width - receptiveField.width; pos.x += stride.width) {
				auto receptedMatrix = submatrix.GetSubmatrix(pos, receptiveField);
				*currPooledElement = ProcessMatrix(std::move(receptedMatrix));
				++currPooledElement;
			}
		}
		dimensions.emplace_back(std::move(pooledMatrix));
	}
	return MultiMatrix(dimensions);
}

auto MaxPooler::ProcessMatrix(const Matrix& matrix) const -> Matrix::element_t {
	return *std::max_element(matrix.begin(), matrix.end());
}

auto MaxPooler::GetSizeAfterPooling(Matrix::Size originalSize) const -> Matrix::Size {
	const auto recep{GetReceptiveField(originalSize)};
	// TODO jnf: factor in overlapping stride
	return {originalSize.height / recep.height, originalSize.width /recep.width};
}
