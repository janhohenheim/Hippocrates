#include <algorithm>
#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ITrainable *> & population, const TrainingParameters & parameters) :
	parameters(parameters),
	geneMutator(parameters)
{
	SetPopulation(population);
}

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ITrainable *> & population, TrainingParameters && parameters) :
    parameters(parameters),
	geneMutator(parameters)
{
	SetPopulation(population);
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

    geneMutator.MutateGenes(childGenes);

	NeuralNetwork child(std::move(childGenes));
	// It may look ineffective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return child;
}

void NeuralNetworkTrainer::ResetPopulation()
{
	for (auto & individuum : population) {
		individuum.trainable->Reset();
	}
}

void NeuralNetworkTrainer::SetPopulation(std::vector<ITrainable*>& population)
{
    this->population.clear();
    for (auto & i : population) {
        NeuralNetwork net = NeuralNetwork(parameters.numberOfInputs, parameters.numberOfOutputs);
        Individuum individuum(i, net);
        this->population.push_back(individuum);
    }
}

void NeuralNetworkTrainer::TrainUntilFitnessEquals(int fitnessToReach) {
	do {
		ResetPopulation();
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
	if (population.empty()) {
		throw std::out_of_range("Your population is empty");
	}
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