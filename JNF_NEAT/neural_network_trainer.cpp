#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ISpecimen *> & population) :
	population(population)
{
}

NeuralNetwork NeuralNetworkTrainer::Breed(const ISpecimen * mother, const ISpecimen * father) const
{
	std::vector<Gene> childGenes;

	if (mother->GetFitness() == father->GetFitness()) {
		// TODO jnf
		// Do Stuff with the genes
	} else {
		// TODO jnf
		// Do Stuff with the genes
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

const ISpecimen * NeuralNetworkTrainer::GetFittestSpecimen() {
	// TODO jnf
	// Implementation
	return population.front();
}

void NeuralNetworkTrainer::LetGenerationLive() {
	for (auto & specimen : population){
		specimen->Update();
		specimen->RecalculateFitness();
	}
}

void NeuralNetworkTrainer::Repopulate() {
	// TODO jnf
	// Implementation
}










