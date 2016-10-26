#pragma once
#include <memory>
#include <functional>
#include "multi_matrix.hpp"
#include "SubSampler/isubsampler.hpp"
#include "multi_matrix_factory.hpp"
#include "SubSampler/Pooler/ipooler.hpp"
#include "SubSampler/neuron.hpp"

namespace Convolutional {

template <typename Pooler, typename Classification>
class NeuralNetwork {
	static_assert(
		std::is_base_of<SubSampler::Pooler::IPooler, Pooler>::value,
		"Pooler must be a descendant of IPooler"
		);
public:	
	Classification ClassifyMultiMatrix(const InputData::IInputData& input) {
		return ClassifyMultiMatrix(MultiMatrixFactory::GetMultiMatrix(input));
	}
	Classification ClassifyMultiMatrix(const MultiMatrix& multiMatrix) {
		auto processedMultiMatrix{ multiMatrix };
		for (const auto& neuron : neurons) {
			processedMultiMatrix = neuron.ProcessMultiMatrix(processedMultiMatrix);
		}
		for (const auto& pooler : poolers) {
			processedMultiMatrix = pooler.ProcessMultiMatrix(processedMultiMatrix);
		}
		return static_cast<Classification>(processedMultiMatrix.GetDimensionCount());
	}

private:
	std::vector<SubSampler::Neuron> neurons;
	std::vector<Pooler> poolers;
};

}
