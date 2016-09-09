#include <memory>
#include "trained_neural_network.h"

using namespace JNF_NEAT;
using namespace std;

auto TrainedNeuralNetwork::LoadFromFile(const ifstream& file) -> TrainedNeuralNetwork {
	auto genome {LoadGenomeFromFile(file)};
	return TrainedNeuralNetwork {move(genome)};
}

auto TrainedNeuralNetwork::SaveToFile(std::ofstream& file) const -> void {
	file << GetGenome().GetJSON();
}

auto TrainedNeuralNetwork::LoadGenomeFromFile(const std::ifstream& file) -> Genome
{
	auto parameters{LoadTrainigParametersFromFile(file)};
	Genome genome{move(parameters)};
	
	// TODO sara: implementation
	bool readAllGenes = false;
	while (!readAllGenes) {
		Gene gene;
		gene.from = 0;
		gene.to = 0;
		gene.weight = 0.0f;
		// etc.

		//genome.AppendGene(move(gene));
		readAllGenes = true;
	}

	return genome;
}

auto TrainedNeuralNetwork::LoadTrainigParametersFromFile(const std::ifstream& file) -> TrainingParameters
{
	// TODO sara: implementation
	unsigned int inputCount = 2;
	unsigned int outputCount = 1;
	TrainingParameters parameters(inputCount, outputCount);
	parameters.advanced.ranges.minWeight = -1.0f;
	parameters.advanced.ranges.maxWeight = 1.0f;
	// etc.

	return parameters;
}
