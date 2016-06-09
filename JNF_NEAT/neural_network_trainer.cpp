#include <algorithm>
#include <stdexcept>
#include "neural_network_trainer.h"
#include <algorithm>

using namespace JNF_NEAT;
using namespace std;

NeuralNetworkTrainer::NeuralNetworkTrainer(vector<IBody*>& population, const TrainingParameters& parameters) :
	parameters(parameters),
	populationSize(population.size()),
	bodies(population)
{
	SetBodies(population);
}

NeuralNetworkTrainer::NeuralNetworkTrainer(vector<IBody*>& population, TrainingParameters&& parameters) :
	parameters(parameters),
	populationSize(population.size()),
	bodies(population)
{
	SetBodies(population);
}

void NeuralNetworkTrainer::ResetPopulationToTeachableState() {
	for (auto& sp : species) {
		sp.ResetToTeachableState();
	}
}

void NeuralNetworkTrainer::SetBodies(vector<IBody*>& bodies) {
	species.clear();

	Genome standardGenes(parameters);
	for (auto& currTrainer : bodies) {
		NeuralNetwork network(standardGenes);
		Organism organism(currTrainer, move(network));
        FillOrganismIntoSpecies(move(organism));
	}
    DeleteEmptySpecies();
}


void NeuralNetworkTrainer::TrainUntilFitnessEquals(double fitnessToReach) {
	LetGenerationLive();
	while (GetFittestOrganism().GetOrCalculateRawFitness() < (fitnessToReach - 1e-6)) {
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

TrainedNeuralNetwork NeuralNetworkTrainer::GetTrainedNeuralNetwork() {
	return TrainedNeuralNetwork(GetFittestOrganism().GetGenome());
}

Organism& NeuralNetworkTrainer::GetFittestOrganism() {
	if (species.empty()) {
		throw out_of_range("Your population is empty");
	}
    auto CompareSpecies = [&](Species& lhs, Species& rhs) {
        return lhs.GetFittestOrganism().GetOrCalculateFitness() < rhs.GetFittestOrganism().GetOrCalculateFitness();
    };

    sort(species.begin(), species.end(), CompareSpecies);
	return species.front().GetFittestOrganism();
}

void NeuralNetworkTrainer::LetGenerationLive() {
	for (unsigned int i = 0; i < parameters.updatesPerGeneration; ++i) {
		for (auto& sp : species) {
			sp.LetPopulationLive();
		}
	}
}

void NeuralNetworkTrainer::PrepareSpeciesForPopulation() {
	AnalyzeAndClearSpeciesPopulation();
	DeleteStagnantSpecies();	
}

void NeuralNetworkTrainer::FillOrganismIntoSpecies(const Organism& organism) {
    bool isCompatibleWithExistingSpecies = false;
    for (auto& currSpecies : species) {
        if (currSpecies.IsCompatible(organism.GetGenome())) {
            currSpecies.AddOrganism(move(organism));
            isCompatibleWithExistingSpecies = true;
            break;
        }
    }
    if (!isCompatibleWithExistingSpecies) {
        Species newSpecies(organism);
        species.push_back(move(newSpecies));
    } 
}

void NeuralNetworkTrainer::FillOrganismIntoSpecies(Organism&& organism) {
	bool isCompatibleWithExistingSpecies = false;
	for (auto& currSpecies : species) {
		if (currSpecies.IsCompatible(organism.GetGenome())) {
			currSpecies.AddOrganism(move(organism));
			isCompatibleWithExistingSpecies = true;
			break;
		}
	}
	if (!isCompatibleWithExistingSpecies) {
		Species newSpecies(move(organism));
		species.push_back(move(newSpecies));
	}
}

void NeuralNetworkTrainer::AnalyzeAndClearSpeciesPopulation() {
	for (auto& currSpecies : species) {
		currSpecies.AnalyzeAndClearPopulation();
	}
}

void NeuralNetworkTrainer::DeleteStagnantSpecies() {
	auto IsStagnant = [](Species& species) {
		return species.IsStagnant();
	};
	auto removePos = remove_if(species.begin(), species.end(), IsStagnant);
	// Let at least one species survive
	if (!species.empty() && removePos == species.begin()) {
		++removePos;
	}
	species.erase(removePos, species.end());
}

void NeuralNetworkTrainer::DeleteEmptySpecies() {
    species.erase(
        remove_if(species.begin(), species.end(), [](const Species& s) {return s.IsEmpty(); }),
        species.end()
    );
}

void NeuralNetworkTrainer::Repopulate() {
    PrepareSpeciesForPopulation();
	auto DidChanceOccure = [](float chance) {
		auto num = rand() % 1000;
		return num < int(1000.0f * chance);
	};

	for (auto& trainer : bodies) {
		Species* sp = &SelectSpeciesToBreed();
		auto& father = sp->GetOrganismToBreed();
		if (DidChanceOccure(parameters.advanced.reproduction.chanceForInterspecialReproduction)){
			sp = &SelectSpeciesToBreed();
		}
		auto& mother = sp->GetOrganismToBreed();
		auto childNeuralNetwork(move(father.BreedWith(mother)));
		Organism child(&*trainer, move(childNeuralNetwork));
        FillOrganismIntoSpecies(move(child));
	}
    DeleteEmptySpecies();
	ResetPopulationToTeachableState();
	// TODO jnf Add Concurrency
}

Species& NeuralNetworkTrainer::SelectSpeciesToBreed() {
	// TODO jnf: Switch to stochastic universal sampling
	if (species.empty()) {
		throw out_of_range("There are no species");
	}
    double totalSpeciesFitness = 0.0;
	for (auto& s : species) {
		totalSpeciesFitness += s.GetFittestOrganism().GetOrCalculateFitness();
	}
	if (totalSpeciesFitness == 0) {
		return species[rand() % species.size()];
	}
	double chance = 0.0;
	auto GetChanceForSpecies = [&chance, &totalSpeciesFitness](Species& species) {
		return chance + (species.GetFittestOrganism().GetOrCalculateFitness() / totalSpeciesFitness);
	};
    while (true) {
        for (auto& s : species) {
            double randNum = (double)(rand() % 10'000) / 9'999.0;
            chance = GetChanceForSpecies(s);
            if (randNum < chance) {
                return s;
            }
        }
    }
}