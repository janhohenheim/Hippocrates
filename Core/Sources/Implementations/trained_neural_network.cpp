#include <memory>
#include "../Headers/trained_neural_network.h"

using namespace Hippocrates;
using namespace std;

auto TrainedNeuralNetwork::LoadFromFile(const ifstream& file) -> TrainedNeuralNetwork {
	auto genome {LoadGenomeFromFile(file)};
	return TrainedNeuralNetwork {move(genome)};
}

auto TrainedNeuralNetwork::SaveToFile(std::ofstream& file) const -> void {
	file << GetGenome().GetJSON();
}

auto TrainedNeuralNetwork::LoadGenomeFromFile(const std::ifstream& file) -> Genome {
	// TODO sara: implementation
	TrainingParameters parameters;
	parameters.ranges.minWeight = -1.0f;
	parameters.ranges.maxWeight = 1.0f;
	// etc.

	std::size_t inputCount = 0;
	std::size_t outputCount = 0;
	Genome genome{ inputCount, outputCount, move(parameters) };
	
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
