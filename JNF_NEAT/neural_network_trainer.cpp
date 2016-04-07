#include <algorithm>
#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ITrainable *> & population) :
	population(population)
{
}

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ITrainable*>& population, Ruleset ruleset) :
	population(population),
	ruleset(ruleset)
{
}

NeuralNetwork NeuralNetworkTrainer::Breed(ITrainable * mother, ITrainable * father)
{
	std::vector<Gene> childGenes;

	if (mother->GetOrCalculateFitness() == father->GetOrCalculateFitness()) {
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

void NeuralNetworkTrainer::TrainUntilFitnessEquals(int fitnessToReach) {
	do {
		Repopulate();
		LetGenerationLive();
	} while (GetFittestSpecimen()->GetOrCalculateFitness() < fitnessToReach);
}

void NeuralNetworkTrainer::TrainUntilGenerationEquals(unsigned int generationsToTrain) {
	for(auto generation = 0U; generation < generationsToTrain; generation++){
		Repopulate();
		LetGenerationLive();
	}
}

ITrainable * NeuralNetworkTrainer::GetFittestSpecimen() {
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

void NeuralNetworkTrainer::MutateGenes(std::vector<Gene> & genes){
	// TODO jnf
	// Implementation
}








