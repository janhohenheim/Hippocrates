#pragma once
#include <memory>
#include <functional>
#include "multi_dimensional_matrix.h"
#include "isubsampler.h"
#include "multi_matrix_factory.h"
#include "iinput_data.h"

namespace Convolutional {

class NeuralNetwork {
public:
	NeuralNetwork(MultiDimensionalMatrix matrix);
	NeuralNetwork(const InputData::IInputData& input) : 
		NeuralNetwork(std::move(MultiMatrixFactory::GetMultiMatrix(input))) {}

	
	auto Subsample(const SubSampler::ISubSampler& subsampler) -> void;

private:
	MultiDimensionalMatrix matrix;
};

}
