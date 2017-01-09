#pragma once
#include "ipooling.h"
#include "layer/layers.hpp"

namespace Convolutional::Layer::ResidualBlock::Pooling {

class Bottlenecked : public IPooling {
public:
	using IPooling::IPooling;
	
	Bottlenecked(Convolution convolution, Convolution projector);

	auto ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<Bottlenecked>(*this); }

private:
	Layers layers;
	Convolution projector;
};

}
