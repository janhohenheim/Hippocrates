#include <algorithm>
#include <stdexcept>
#include "neural_network_trainer.h"

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<IBody*>& population, const TrainingParameters& parameters) :
	parameters(parameters),
	populationSize(population.size()),
	trainers(population)
{
	SetBodies(population);
}

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<IBody*>& population, TrainingParameters&& parameters) :
    parameters(parameters),
	populationSize(population.size()),
	trainers(population)
{
	SetBodies(population);
}

void NeuralNetworkTrainer::ResetPopulationToTeachableState()
{
	for (auto& sp : species) {
		sp.ResetToTeachableState();
	}
}

void NeuralNetworkTrainer::SetBodies(std::vector<IBody*>& bodies)
{
	std::vector<Organism> organisms;
	organisms.reserve(bodies.size());
	Genome standardGenes(parameters);
    for (auto& currTrainer : bodies) {
		NeuralNetwork network(standardGenes);
		Organism organism(currTrainer, std::move(network));
		organisms.push_back(std::move(organism));
    }
	CategorizeOrganismsIntoSpecies(std::move(organisms));
}


void NeuralNetworkTrainer::TrainUntilFitnessEquals(int fitnessToReach) {
	LetGenerationLive();
	while (GetFittestOrganism().GetOrCalculateFitness() < fitnessToReach) {
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

TrainedNeuralNetwork NeuralNetworkTrainer::GetTrainedNeuralNetwork()
{
    return TrainedNeuralNetwork(GetFittestOrganism().GetNetwork());
}

Organism& NeuralNetworkTrainer::GetFittestOrganism() {
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
		auto childNeuralNetwork = father.BreedWith(mother);
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
    for (auto& currSpecies : species) {
        currSpecies.Clear();
    }
    for (auto& organism : organisms) {
		bool isCompatibleWithExistingSpecies = false;
		for (auto& currSpecies : species) {
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