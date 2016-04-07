#include <algorithm>
#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(NeuralNetworkTrainer::TrainingParameters parameters) :
	parameters(parameters)
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

	if (ShouldMutate()) {
		MutateGenes(childGenes);
	}

	NeuralNetwork child(childGenes);
	// It may look ineffective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return child;
}

void NeuralNetworkTrainer::SetPopulation(std::vector<ITrainable*>& population)
{
	// TODO jnf
	// Implementation
}

void NeuralNetworkTrainer::TrainUntilFitnessEquals(int fitnessToReach) {
	do {
		Repopulate();
		LetGenerationLive();
	} while (GetFittestSpecimen().trainable->GetOrCalculateFitness() < fitnessToReach);
}

void NeuralNetworkTrainer::TrainUntilGenerationEquals(unsigned int generationsToTrain) {
	for(auto generation = 0U; generation < generationsToTrain; generation++){
		Repopulate();
		LetGenerationLive();
	}
}

NeuralNetworkTrainer::Individuum NeuralNetworkTrainer::GetFittestSpecimen() {
	// TODO jnf
	// Implementation
	return population.front();
}

void NeuralNetworkTrainer::LetGenerationLive() {
	for (auto & specimen : population){
		specimen.trainable->Update();
	}
}

void NeuralNetworkTrainer::Repopulate() {
	// TODO jnf
	// Implementation
}

bool NeuralNetworkTrainer::ShouldMutate()
{
	// TODO jnf
	// Implementation
	return true;
}

void NeuralNetworkTrainer::MutateGenes(std::vector<Gene> & genes){
	// TODO jnf
	// Implementation
}








