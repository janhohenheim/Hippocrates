#pragma once
#include "layer/convolution.hpp"

namespace Convolutional::Layer {

class DimensionScaler : public Convolution {
public:
	DimensionScaler(std::size_t outputDimensionCount, Matrix::Size stride = {1, 1}, Matrix::Size padding = {0, 0})
		: Convolution {outputDimensionCount, Layer::Filter {{1, 1}, std::move(stride), std::move(padding)}} {}
	
	auto Clone() const noexcept->std::unique_ptr<ILayer> override { return std::make_unique<DimensionScaler>(*this); }
};

}
