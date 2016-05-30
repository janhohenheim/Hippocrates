#include <memory>
#include "trained_neural_network.h"

TrainedNeuralNetwork::TrainedNeuralNetwork(const NeuralNetwork& network):
	trainedNetwork(network)
{
}

TrainedNeuralNetwork::TrainedNeuralNetwork(NeuralNetwork&& network) :
	trainedNetwork(std::move(network))
{
}

std::vector<float> TrainedNeuralNetwork::GetOutputs(const std::vector<float>& inputs)
{
	trainedNetwork.SetInputs(inputs);
	return trainedNetwork.GetOutputs();
}

TrainedNeuralNetwork TrainedNeuralNetwork::LoadFromFile(const std::string& fileName)
{
	// TODO jnf Implementation
	std::unique_ptr<TrainingParameters> params (new TrainingParameters);
	params->numberOfInputs = 2;
	params->numberOfOutputs = 1;
	params->updatesPerGeneration =30;
	Genome g(*params.get());
	NeuralNetwork n(std::move(g));
	return TrainedNeuralNetwork(std::move(n));
}

void TrainedNeuralNetwork::SaveToFile(const std::string& fileName) const
{
	// TODO jnf Implementation
}

