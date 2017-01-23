#pragma once
#include "ilayer.hpp"

namespace Convolutional::Layer {
class ReLU : public ILayer {
public:
	using ILayer::ILayer;
	auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override { return dimensionality; }

	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return size; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return {0, 0}; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }
	
	auto Clone() const noexcept->std::unique_ptr<ILayer> override { return std::make_unique<ReLU>(*this); }
};

}
