#pragma once
#include "filter.hpp"

namespace Convolutional::Layer {
class Convolution : public ILayer {
public:
	using ILayer::ILayer;
	Convolution(std::size_t filterCount, const Filter& init): convolution{ filterCount, init} {}

	auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;
	
	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return convolution.front().GetReceptiveField(size); }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return convolution.front().GetZeroPadding(size); }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return convolution.front().GetStride(size); }

	auto Clone() const noexcept->std::unique_ptr<ILayer> override { return std::make_unique<Convolution>(*this); }

	auto GetFilterCount() const noexcept { return convolution.size(); }

private:
	std::vector<Filter> convolution;
};

}
