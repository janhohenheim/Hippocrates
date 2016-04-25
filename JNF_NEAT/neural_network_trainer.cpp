#include <algorithm>
#include <stdexcept>
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

NeuralNetwork NeuralNetworkTrainer::Breed(ITrainable * mother, ITrainable * father) const
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
		individuum.Reset();
	}
}

void NeuralNetworkTrainer::SetPopulation(std::vector<ITrainable*>& population)
{
    this->population.clear();
	this->population.reserve(population.size());
    for (auto & currTrainable : population) {
		// TODO jnf
		// Every Individual generates Genes with historical markings up to population.size() * parameters.numberOfInputs * parameters.NumberOfOutputs
		// Instead, the historical markings should only go to parameters.numberOfInputs * parameters.NumberOfOutputs
		// and be identical to every other individuals genes (but still having random weights)
		this->population.push_back({ currTrainable, parameters });
    }
	CategorizePopulationIntoSpecies();
}


void NeuralNetworkTrainer::TrainUntilFitnessEquals(int fitnessToReach) {
	LetGenerationLive();
	while (GetFittestSpecimen().GetOrCalculateFitness() < fitnessToReach) {
		Repopulate();
		ResetPopulation();
		for (unsigned int i = 0; i < parameters.updatesPerGeneration; ++i) {
			LetGenerationLive();
		}
	}
}

void NeuralNetworkTrainer::TrainUntilGenerationEquals(unsigned int generationsToTrain) {
	for(auto generation = 0U; generation < generationsToTrain; generation++){
		Repopulate();
		LetGenerationLive();
	}
}

Individual & NeuralNetworkTrainer::GetFittestSpecimen() {
	if (population.empty()) {
		throw std::out_of_range("Your population is empty");
	}

	auto compareFitness = [](Individual & lhs, Individual & rhs) {
		return lhs.GetOrCalculateFitness() < rhs.GetOrCalculateFitness();
	};
	// TODO jnf
	// cache this
	return *std::max_element(population.begin(), population.end(), compareFitness);
}

void NeuralNetworkTrainer::LetGenerationLive() {
	for (auto & individual : population){
		individual.Update();
	}
}

void NeuralNetworkTrainer::Repopulate() {
	// TODO jnf
	// Implementation
	CategorizePopulationIntoSpecies();
    // TODO jnf
    // Add Concurrency
}


void NeuralNetworkTrainer::CategorizePopulationIntoSpecies()
{
	for (auto & individual : population) {
		bool isCompatibleWithExistingSpecies = false;
		for (auto & currSpecies : species) {
			if (currSpecies.IsCompatible(individual.GetGenes())) {
				individual.CoupleWithSpecies(currSpecies);
				isCompatibleWithExistingSpecies = true;
				break;
			}
		}
		if (!isCompatibleWithExistingSpecies) {
			Species newSpecies(parameters);
			species.push_back(std::move(newSpecies));
			individual.CoupleWithSpecies(species.back());
		}
	}
	// TODO jnf
	// Clear empty species
}