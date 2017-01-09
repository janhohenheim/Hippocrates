#include "layer/residual_block/pooling/bottlenecked.hpp"
#include "layer/relu.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;
using namespace Convolutional::Layer::ResidualBlock;
using namespace Convolutional::Layer::ResidualBlock::Pooling;

Bottlenecked::Bottlenecked(const Convolution& convolution, Filter projector, std::size_t factor)
: 
	layers {
		ReLU {},
		Convolution {convolution.GetFilterCount(), Layer::Filter {{1, 1}}},
		ReLU {},
		Convolution {convolution},
		ReLU {},
		Convolution {convolution.GetFilterCount() * factor, Layer::Filter {{1, 1}}}
	},
	projector{convolution.GetFilterCount() * factor, std::move(projector)}
{
}

auto Bottlenecked::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	const auto processed = layers.ProcessMultiMatrix(multiMatrix);
	const auto projection = projector.ProcessMultiMatrix(multiMatrix);
	return processed + projection;
}

auto Bottlenecked::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	return layers.GetDimensionalityAfterProcessing(dimensionality);
}
