#include "layer/residual_block/normal.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;
using namespace Convolutional::Layer::ResidualBlock;

Normal::Normal(Convolution convolution, std::size_t convolutionCount) {
	std::vector<Layers::Layer_t> layers;
	layers.reserve(convolutionCount * 2);

	for (std::size_t i = 0; i < convolutionCount; ++i) {
		layers.push_back(std::make_unique<ReLU>());
		layers.push_back(convolution.Clone());
	}

	this->layers = Layers {std::move(layers)};
}

auto Normal::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	return layers.ProcessMultiMatrix(multiMatrix);
}

auto Normal::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	return layers.GetDimensionalityAfterProcessing(dimensionality);
}
