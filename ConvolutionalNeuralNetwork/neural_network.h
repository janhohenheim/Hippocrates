#pragma once
#include <memory>
#include <functional>
#include "multi_matrix.h"
#include "isubsampler.h"
#include "multi_matrix_factory.h"
#include "ipooler.h"
#include "neuron.h"

namespace Convolutional {

template <typename Classification>
class NeuralNetwork {
public:	
	template <typename ... Ts>
	explicit NeuralNetwork(Ts&&... params) {
		// std::move should be replaced with std::forward here, but MSVC is buggy in this case
		int dummy[] =
		{0, (layers.emplace_back(std::make_unique<Ts>(std::move(params))), 0)...};
		static_cast<void>(dummy); // avoid unused variable warning

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
