#pragma once
#include <memory>
#include <functional>
#include "multi_matrix.h"
#include "isubsampler.h"
#include "multi_matrix_factory.h"
#include "iinput_data.h"

namespace Convolutional {

class NeuralNetwork {
public:
	NeuralNetwork(MultiMatrix matrix);
	NeuralNetwork(const InputData::IInputData& input) : 
		NeuralNetwork(std::move(MultiMatrixFactory::GetMultiMatrix(input))) {}

	
	auto Subsample(const SubSampler::ISubSampler& subsampler) -> void;

private:
	MultiMatrix matrix;
};

}
