#pragma once
#include <memory>
#include "multi_matrix.hpp"
#include "Layer/layers.hpp"
#include "multi_matrix_factory.hpp"
#include "Layer/filter.hpp"

namespace Convolutional {

template <typename Classification>
class NeuralNetwork {
public:	
	explicit NeuralNetwork(Layer::Layers&& layers) : layersByValue{std::move (layers)}, layers{ layersByValue } {	}
	explicit NeuralNetwork(Layer::Layers& layers) : layers{ layers } {	}

	auto ClassifyMultiMatrix(const InputData::IInputData& input) {
		return ClassifyMultiMatrix(MultiMatrixFactory::GetMultiMatrix(input));
	}

	auto ClassifyMultiMatrix(const MultiMatrix& multiMatrix) {
		auto processedMultiMatrix{ multiMatrix };
		for (const auto& layer : layers) {
			processedMultiMatrix = layer->ProcessMultiMatrix(processedMultiMatrix);
		}
		return static_cast<Classification>(processedMultiMatrix.GetDimensionCount());
	}

private:
	[[maybe_unused]] Layer::Layers layersByValue;
	Layer::Layers& layers;
};

}
