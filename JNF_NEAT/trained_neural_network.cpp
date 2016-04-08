#include "trained_neural_network.h"

TrainedNeuralNetwork::TrainedNeuralNetwork(const NeuralNetwork & trainedNetwork):
	trainedNetwork(trainedNetwork)
{
}

std::vector<float> TrainedNeuralNetwork::GetOutputs(const std::vector<float>& inputs)
{
	trainedNetwork.SetInputs(inputs);
	return trainedNetwork.GetOrCalculateOutputs();
}

void TrainedNeuralNetwork::LoadFromFile(const std::string & fileName)
{
	// TODO jnf
	// Implementation
}

void TrainedNeuralNetwork::SaveToFile(const std::string & fileName) const
{
	// TODO jnf
	// Implementation
}
