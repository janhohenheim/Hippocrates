#pragma once
#include "layer/residual_block/iresidual_block.hpp"
#include "layer/layers.hpp"


namespace Convolutional::Layer::ResidualBlock {

class Normal : public IResidualBlock {
public:
	using IResidualBlock::IResidualBlock;
	
	Normal(Convolution convolution, std::size_t convolutionCount);

	auto ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<Normal>(*this); }

private:
	Layers layers;
};

}
