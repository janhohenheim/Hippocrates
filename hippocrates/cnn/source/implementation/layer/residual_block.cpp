#include "layer/residual_block.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto ResidualBlock::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	return multiMatrix;
}

auto ResidualBlock::GetSizeAfterProcessing() const noexcept -> Matrix::Size {
	return Matrix::Size();
}

auto ResidualBlock::GetElementCountAfterProcessing() const noexcept -> std::size_t {
	return std::size_t();
}
