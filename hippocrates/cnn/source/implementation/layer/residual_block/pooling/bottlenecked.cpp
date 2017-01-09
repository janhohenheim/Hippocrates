#include "layer/residual_block/pooling/bottlenecked.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;
using namespace Convolutional::Layer::ResidualBlock;
using namespace Convolutional::Layer::ResidualBlock::Pooling;

Bottlenecked::Bottlenecked(Convolution convolution, Convolution projector)
: 
	layers {
		ReLU {},
		Convolution {convolution.GetFilterCount()},
		ReLU {},
		Convolution {convolution},
		ReLU {},
		Convolution {convolution.GetFilterCount() * 4}
	},
	projector{std::move(projector)}
{
}

auto Bottlenecked::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	const auto projection = projector.ProcessMultiMatrix(multiMatrix);
	return layers.ProcessMultiMatrix(multiMatrix) + projection;
}

auto Bottlenecked::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	return layers.GetDimensionalityAfterProcessing(dimensionality);
}
