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
	for (auto& individuum : population) {
		individuum.Reset();
	}
}

void NeuralNetworkTrainer::SetPopulation(std::vector<ITrainable*>& population)
{
    this->population.clear();
	this->population.reserve(population.size());
	Genome standardGenes(parameters);
    for (auto& currTrainable : population) {
		NeuralNetwork network(standardGenes);
		Individual individual(currTrainable, std::move(network));
		this->population.push_back(std::move(individual));
    }
	CategorizePopulationIntoSpecies();
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

Individual& NeuralNetworkTrainer::GetFittestSpecimen() {
	if (population.empty()) {
		throw std::out_of_range("Your population is empty");
	}

	auto compareFitness = [](Individual& lhs, Individual& rhs) {
		return lhs.GetOrCalculateFitness() < rhs.GetOrCalculateFitness();
	};
	// TODO jnf cache this
	return *std::max_element(population.begin(), population.end(), compareFitness);
}

void NeuralNetworkTrainer::LetGenerationLive() {
	for (unsigned int i = 0; i < parameters.updatesPerGeneration; ++i) {
		for (auto& individual : population) {
			individual.Update();
		}
	}
}

void NeuralNetworkTrainer::Repopulate() {
	std::vector<Individual> newPopulation;
	newPopulation.reserve(population.size());
	for (auto& individual : population) {
        auto & father = SelectIndividualToBreed();
        auto & mother = SelectIndividualToBreed();

        auto childGenome(father.BreedWith(mother));
        NeuralNetwork childNeuralNetwork(std::move(childGenome));
        Individual child(individual.GetTrainable(), std::move(childNeuralNetwork));
        newPopulation.push_back(std::move(child));
	}
	population = std::move(newPopulation);
	CategorizePopulationIntoSpecies();
	ResetPopulationToTeachableState();
    // TODO jnf Add Concurrency
}

Individual & NeuralNetworkTrainer::SelectIndividualToBreed() {
    // TODO jnf: Implement fitness proportionate selection
    // TODO jnf: Switch later to stochastic universal sampling
    return population[0];
}

void NeuralNetworkTrainer::CategorizePopulationIntoSpecies()
{
	for (auto& individual : population) {
		bool isCompatibleWithExistingSpecies = false;
		for (auto& currSpecies : species) {
            currSpecies.Clear();
			if (currSpecies.IsCompatible(individual.GetGenome())) {
				individual.CoupleWithSpecies(currSpecies);
				isCompatibleWithExistingSpecies = true;
				break;
			}
		}
		if (!isCompatibleWithExistingSpecies) {
			species.push_back(std::move(Species()));
			individual.CoupleWithSpecies(species.back());
		}
	}
	// TODO jnf Clear empty species
}