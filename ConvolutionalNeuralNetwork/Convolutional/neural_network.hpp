#pragma once
#include <memory>
#include <functional>
#include "multi_matrix.hpp"
#include "SubSampler/isubsampler.hpp"
#include "multi_matrix_factory.hpp"
#include "SubSampler/Pooler/ipooler.hpp"
#include "SubSampler/neuron.hpp"

namespace Convolutional {

template <typename Classification>
class NeuralNetwork {
public:	
	template <typename ... Ts>
	explicit NeuralNetwork(Ts&&... params) {
		[[maybe_unused]]
		volatile int dummy[] =
		{0, (layers.emplace_back(std::make_unique<Ts>(std::forward<Ts>(params))), 0)...};

	}
	Classification ClassifyMultiMatrix(const InputData::IInputData& input) {
		return ClassifyMultiMatrix(MultiMatrixFactory::GetMultiMatrix(input));
	}
	Classification ClassifyMultiMatrix(const MultiMatrix& multiMatrix) {
		auto processedMultiMatrix{ multiMatrix };
		for (const auto& layer : layers) {
			processedMultiMatrix = layer->ProcessMultiMatrix(processedMultiMatrix);
		}
		return static_cast<Classification>(processedMultiMatrix.GetDimensionCount());
	}

private:
	std::vector<SubSampler::Neuron> neurons;
	using SubSampler_t = std::unique_ptr<SubSampler::ISubSampler>;
	std::vector<SubSampler_t> layers;
};

}
