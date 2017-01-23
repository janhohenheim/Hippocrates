#include "layer/residual_block.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto ResidualBlock::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	auto mm = multiMatrix;
	for (size_t i = 0; i < layers.size(); ++i) {
		mm = layers[i]->ProcessMultiMatrix(mm);
	}
	mm += multiMatrix;
	mm = layers.back()->ProcessMultiMatrix(mm);
	return mm;
}

auto ResidualBlock::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	// TODO jnf: is this correct?
	return layers.GetDimensionalityAfterProcessing(dimensionality);
}

auto ResidualBlock::GetSizeAfterProcessing() const noexcept -> Matrix::Size {
	return Matrix::Size();
}

auto ResidualBlock::GetElementCountAfterProcessing() const noexcept -> std::size_t {
	return std::size_t();
}
