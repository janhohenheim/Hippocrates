#include "layer/residual_block/bottlenecked.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;
using namespace Convolutional::Layer::ResidualBlock;

Bottlenecked::Bottlenecked(Convolution convolution)
: 
	layers {
		ReLU {},
		Convolution {convolution.GetFilterCount()},
		ReLU {},
		std::move(convolution),
		ReLU {},
		Convolution {convolution.GetFilterCount() * 4}
	}
{
}

auto Bottlenecked::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	return layers.ProcessMultiMatrix(multiMatrix);
}

auto Bottlenecked::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	return layers.GetDimensionalityAfterProcessing(dimensionality);
}
