#include "layer/residual_block/normal.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;
using namespace Convolutional::Layer::ResidualBlock;

auto Normal::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	auto mm = multiMatrix;
	for (size_t i = 0; i < layers.size(); ++i) {
		mm = layers[i]->ProcessMultiMatrix(mm);
	}
	mm += multiMatrix;
	mm = layers.back()->ProcessMultiMatrix(mm);
	return mm;
}

auto Normal::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	// TODO jnf: is this correct?
	return layers.GetDimensionalityAfterProcessing(dimensionality);
}
