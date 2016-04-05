#include <algorithm>
#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ITrainable *> & population) :
	population(population)
{
}

NeuralNetwork NeuralNetworkTrainer::Breed(const ITrainable * mother, const ITrainable * father) const
{
	std::vector<Gene> childGenes;

	if (mother->GetFitness() == father->GetFitness()) {
		// TODO jnf
		// Do Stuff with the genes
	} else {
		// TODO jnf
		// Do Stuff with the genes
	}

	/*if (ChanceForMutation()*/ {
		MutateGenes(childGenes);
	}

	NeuralNetwork child(childGenes);
	// It may look ineffective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return child;
}

void NeuralNetworkTrainer::TrainUntilFitnessEquals(unsigned int fitnessToReach) {
	do {
		Repopulate();
		LetGenerationLive();
	} while (GetFittestSpecimen()->GetFitness() < fitnessToReach);
}

void NeuralNetworkTrainer::TrainUntilGenerationEquals(unsigned int generationsToTrain) {
	for(auto generation = 0U; generation < generationsToTrain; generation++){
		Repopulate();
		LetGenerationLive();
	}
}

const ITrainable * NeuralNetworkTrainer::GetFittestSpecimen() {
	// TODO jnf
	// Implementation
	return population.front();
}

void NeuralNetworkTrainer::LetGenerationLive() {
	for (auto & specimen : population){
		specimen->Update();
	}
}

void NeuralNetworkTrainer::Repopulate() {
	// TODO jnf
	// Implementation
}

void NeuralNetworkTrainer::MutateGenes(std::vector<Gene> & genes) const{
	struct neuronBirthInfo {
		unsigned neuron = 0L;
		unsigned layer = 0L;
		std::vector<unsigned> destinations;
	};

	std::vector<neuronBirthInfo> neuronBirthInfos;

	const unsigned int LOWEST_POSSIBLE_LAYER = 0;

	for (auto & gene : genes) {

		auto isFrom = [&gene](neuronBirthInfo info) {
			return info.neuron == gene.from;
		};
		auto isTo = [&gene](neuronBirthInfo info) {
			return info.neuron == gene.to;
		};
		auto fromGene = std::find_if(neuronBirthInfos.begin(), neuronBirthInfos.end(), isFrom);
		auto toGene = std::find_if(neuronBirthInfos.begin(), neuronBirthInfos.end(), isTo);

		bool fromExists = fromGene != neuronBirthInfos.end();
		bool toExists = toGene != neuronBirthInfos.end();

		if (!fromExists && !toExists) {
			neuronBirthInfo fromInfo;
			fromInfo.neuron = gene.from;
			fromInfo.layer = LOWEST_POSSIBLE_LAYER;
			fromInfo.destinations = {gene.to};
			neuronBirthInfos.push_back(fromInfo);

			neuronBirthInfo toInfo;
			toInfo.neuron = gene.to;
			toInfo.layer = LOWEST_POSSIBLE_LAYER + 1;
			neuronBirthInfos.push_back(toInfo);
		} else if (!fromExists && toExists) {
			// TODO jnf
			// Implement
		} else if (fromExists && !toExists) {
			neuronBirthInfo toInfo;

			toInfo.neuron = gene.to;
			toInfo.layer = (*fromGene).layer + 1;
			(*fromGene).destinations.push_back(toInfo.neuron);
			// TODO jnf
			// Implement
			neuronBirthInfos.push_back(toInfo);
		} else if (fromExists && toExists) {
			(*fromGene).destinations.push_back((*toGene).neuron);
			// TODO jnf
			// Implement
		}
	}
}








