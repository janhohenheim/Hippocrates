#include "trained_neural_network.h"

TrainedNeuralNetwork::TrainedNeuralNetwork(const Genome& genome):
	trainedNetwork(genome)
{
}

TrainedNeuralNetwork::TrainedNeuralNetwork(Genome&& genome) :
    trainedNetwork(std::move(genome))
{
}

std::vector<float> TrainedNeuralNetwork::GetOutputs(const std::vector<float>& inputs)
{
	trainedNetwork.SetInputs(inputs);
	return trainedNetwork.GetOutputs();
}

void TrainedNeuralNetwork::LoadFromFile(const std::string& fileName)
{
	// TODO jnf Implementation
}

void TrainedNeuralNetwork::SaveToFile(const std::string& fileName) const
{
	// TODO jnf Implementation
}