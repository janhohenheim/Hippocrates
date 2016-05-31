#include <memory>
#include "trained_neural_network.h"

TrainedNeuralNetwork TrainedNeuralNetwork::LoadFromFile(const std::string& fileName)
{
	// TODO jnf Implementation
	std::unique_ptr<TrainingParameters> params (new TrainingParameters);
	params->numberOfInputs = 2;
	params->numberOfOutputs = 1;
	params->updatesPerGeneration =30;
	TrainedNeuralNetwork net(*params.get());
	return net;
}

void TrainedNeuralNetwork::SaveToFile(const std::string& fileName) const
{
	// TODO jnf Implementation
}

std::string TrainedNeuralNetwork::GetGenomeAsString() const{
	std::string genomeString;
	for (auto& gene : GetGenome()) {
		genomeString +=
			"Gene with marking #" + std::to_string(gene.historicalMarking) + ":\n"
			+ "\t	from: " + std::to_string(gene.from) + "\n"
			+ "\t	to: " + std::to_string(gene.to) + "\n"
			+ "\t	weight: " + std::to_string(gene.weight) + "\n"
			+ "\t	is enabled: " + std::to_string(gene.isEnabled) + "\n\n";
	}
	return genomeString;
}