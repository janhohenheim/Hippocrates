#include <algorithm>
#include <stdexcept>
#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ITrainable*>& population, const TrainingParameters& parameters) :
	parameters(parameters)
{
	SetPopulation(population);
}

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<ITrainable*>& population, TrainingParameters&& parameters) :
    parameters(parameters)
{
	SetPopulation(population);
}




void NeuralNetworkTrainer::ResetPopulationToTeachableState()
{
	for (auto& sp : species) {
		sp.ResetToTeachableState();
	}
}

void NeuralNetworkTrainer::SetPopulation(std::vector<ITrainable*>& population)
{
	std::vector<Organism> organisms;
	organisms.reserve(population.size());
	Genome standardGenes(parameters);
    for (auto& currTrainable : population) {
		NeuralNetwork network(standardGenes);
		Organism organism(currTrainable, std::move(network));
		organisms.push_back(std::move(organism));
    }
	CategorizeOrganismsIntoSpecies(std::move(organisms));
}


void NeuralNetworkTrainer::TrainUntilFitnessEquals(int fitnessToReach) {
	LetGenerationLive();
	while (GetFittestSpecimen().GetOrCalculateFitness() < fitnessToReach) {
		Repopulate();
		LetGenerationLive();
	}
}

void NeuralNetworkTrainer::TrainUntilGenerationEquals(unsigned int generationsToTrain) {
	LetGenerationLive();
	for (unsigned int i = 0; i < generationsToTrain; ++i) {
		Repopulate();
		LetGenerationLive();
	}
}

Organism& NeuralNetworkTrainer::GetFittestSpecimen() {
	if (species.empty()) {
		throw std::out_of_range("Your population is empty");
	}

	auto compareFitness = [](Organism& lhs, Organism& rhs) {
		return lhs.GetOrCalculateFitness() < rhs.GetOrCalculateFitness();
	};
	// TODO jnf implementation
	// return *std::max_element(population.begin(), population.end(), compareFitness);
}

void NeuralNetworkTrainer::LetGenerationLive() {
	for (unsigned int i = 0; i < parameters.updatesPerGeneration; ++i) {
		for (auto& sp : species) {
			sp.LetPopulationLive();
		}
	}
}

void NeuralNetworkTrainer::Repopulate() {
	// TODO jnf: Implement
	std::vector<Organism> population;
	//population.reserve(size);
	/*
	for (auto& organism : population) {
        auto & father = SelectOrganismToBreed();
        auto & mother = SelectOrganismToBreed();

        auto childGenome(father.BreedWith(mother));
        NeuralNetwork childNeuralNetwork(std::move(childGenome));
        Organism child(organism.GetTrainable(), std::move(childNeuralNetwork));
        population.push_back(std::move(child));
	}
	 */
	CategorizeOrganismsIntoSpecies(std::move(population));
	ResetPopulationToTeachableState();
    // TODO jnf Add Concurrency
}

Organism & NeuralNetworkTrainer::SelectOrganismToBreed() {
    // TODO jnf: Implement fitness proportionate selection
    // TODO jnf: Switch later to stochastic universal sampling
}

void NeuralNetworkTrainer::CategorizeOrganismsIntoSpecies(std::vector<Organism> && organisms) {
	for (auto& organism : organisms) {
		bool isCompatibleWithExistingSpecies = false;
		for (auto& currSpecies : species) {
            currSpecies.Clear();
			if (currSpecies.IsCompatible(organism.GetGenome())) {
				currSpecies.AddOrganism(std::move(organism));
				isCompatibleWithExistingSpecies = true;
				break;
			}
		}
		if (!isCompatibleWithExistingSpecies) {
			species.push_back(std::move(Species()));
			species.back().AddOrganism(std::move(organism));
		}
	}
	// TODO jnf Clear empty species
}