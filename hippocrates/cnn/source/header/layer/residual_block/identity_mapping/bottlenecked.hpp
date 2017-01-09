#pragma once
#include "iidentity_mapping.hpp"
#include "layer/layers.hpp"

namespace Convolutional::Layer::ResidualBlock::IdentityMapping {

class Bottlenecked : public IIdentityMapping {
public:
	using IIdentityMapping::IIdentityMapping;
	
	Bottlenecked(Convolution convolution);

	auto ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<Bottlenecked>(*this); }

private:
	Layers layers;
};

}
