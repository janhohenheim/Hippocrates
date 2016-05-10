#include <algorithm>
#include <stdexcept>
#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<INetworkTrainer*>& population, const TrainingParameters& parameters) :
	parameters(parameters),
	populationSize(population.size()),
	trainers(population)
{
	SetPopulation(population);
}

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<INetworkTrainer*>& population, TrainingParameters&& parameters) :
    parameters(parameters),
	populationSize(population.size()),
	trainers(population)
{
	SetPopulation(population);
}

void NeuralNetworkTrainer::ResetPopulationToTeachableState()
{
	for (auto& sp : species) {
		sp.ResetToTeachableState();
	}
}

void NeuralNetworkTrainer::SetPopulation(std::vector<INetworkTrainer*>& population)
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
	return species.front().GetFittestOrganism();
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
	population.reserve(populationSize);

	auto DidChanceOccure = [](float chance) {
		auto num = rand() % 100;
		return num < int(100.0f * chance);
	};

	for (auto& trainer : trainers) {
		Species* sp = &SelectSpeciesToBreed();
		auto & father = sp->GetOrganismToBreed();
		if (DidChanceOccure(parameters.advanced.reproduction.chanceForInterspecialReproduction)){
			sp = &SelectSpeciesToBreed();
		}
		auto & mother = sp->GetOrganismToBreed();
		auto childGenome = father.BreedWith(mother);

		NeuralNetwork childNeuralNetwork(std::move(childGenome));
		Organism child(&*trainer, std::move(childNeuralNetwork));
		population.push_back(std::move(child));
	}
	CategorizeOrganismsIntoSpecies(std::move(population));
	ResetPopulationToTeachableState();
    // TODO jnf Add Concurrency
}

Species &NeuralNetworkTrainer::SelectSpeciesToBreed() {
	// TODO jnf: Implement fitness proportionate selection
	// TODO jnf: Switch later to stochastic universal sampling
	return species.front();
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

	auto CompareSpecies = [&](Species& lhs, Species& rhs) {
		return lhs.GetFittestOrganism().GetOrCalculateFitness() < rhs.GetFittestOrganism().GetOrCalculateFitness();
	};
	std::sort(species.begin(), species.end(), CompareSpecies);
	for (auto& sp : species){
		sp.SetPopulationsFitnessModifier();
	}
}