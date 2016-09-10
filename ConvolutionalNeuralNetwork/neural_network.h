#pragma once
#include <memory>
#include <functional>
#include "multi_matrix.h"
#include "isubsampler.h"
#include "multi_matrix_factory.h"
#include "ipooler.h"
#include "neuron.h"

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
		return static_cast<Classification>(multiMatrix.GetDimensionCount());
	}

private:
	auto Subsample(const SubSampler::ISubSampler& subsampler) {
		matrix = subsampler.ProcessMultiMatrix(matrix);
	}
	std::vector<SubSampler::Neuron> neurons;
	std::vector<Pooler> poolers;
};

}
