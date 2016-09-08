#include "neural_network.h"

using namespace Convolutional;


NeuralNetwork::NeuralNetwork(MultiMatrix matrix):
	matrix(std::move(matrix))
{
}

auto Convolutional::NeuralNetwork::Subsample(const SubSampler::ISubSampler & subsampler) -> void {
	matrix = subsampler.ProcessMultiMatrix(matrix);
}
