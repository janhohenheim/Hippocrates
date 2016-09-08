#include "neural_network.h"

using namespace Convolutional;


NeuralNetwork::NeuralNetwork(MultiDimensionalMatrix matrix) :
	matrix(std::move(matrix))
{
}

auto Convolutional::NeuralNetwork::Subsample(const SubSampler::ISubSampler & subsampler) -> void {
	matrix = subsampler.ProcessMultiMatrix(matrix);
}
