#include "layer/residual_block/identity_mapping/bottlenecked.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;
using namespace Convolutional::Layer::ResidualBlock;
using namespace Convolutional::Layer::ResidualBlock::IdentityMapping;

Bottlenecked::Bottlenecked(Convolution convolution)
: 
	layers {
		ReLU {},
		Convolution {convolution.GetFilterCount()},
		ReLU {},
		convolution,
		ReLU {},
		Convolution {convolution.GetFilterCount() * 4}
	}
{
}

auto Bottlenecked::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	//return layers.ProcessMultiMatrix(multiMatrix) + multiMatrix;
}

auto Bottlenecked::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	return dimensionality;
}
