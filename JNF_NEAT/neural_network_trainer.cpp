#include <algorithm>
#include <stdexcept>
#include "neural_network_trainer.h"
#include <algorithm>

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<IBody*>& population, const TrainingParameters& parameters) :
	parameters(parameters),
	populationSize(population.size()),
	bodies(population)
{
	SetBodies(population);
}

NeuralNetworkTrainer::NeuralNetworkTrainer(std::vector<IBody*>& population, TrainingParameters&& parameters) :
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

void NeuralNetworkTrainer::SetBodies(std::vector<IBody*>& bodies) {
    PrepareSpeciesForPopulation();
	Genome standardGenes(parameters);
	for (auto& currTrainer : bodies) {
		NeuralNetwork network(standardGenes);
		Organism organism(currTrainer, std::move(network));
        FillOrganismIntoSpecies(std::move(organism));
	}
    DeleteEmptySpecies();
}


void NeuralNetworkTrainer::TrainUntilFitnessEquals(size_t fitnessToReach) {
	LetGenerationLive();
	while (GetFittestOrganism().GetOrCalculateRawFitness() < fitnessToReach) {
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
		throw std::out_of_range("Your population is empty");
	}
    auto CompareSpecies = [&](Species& lhs, Species& rhs) {
        return lhs.GetFittestOrganism().GetOrCalculateFitness() < rhs.GetFittestOrganism().GetOrCalculateFitness();
    };

    std::sort(species.begin(), species.end(), CompareSpecies);
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
    for (auto& currSpecies : species) {
        currSpecies.Clear();
    }

    for (auto& s = species.begin(); s != species.end() && species.size() > 1; ) {
        if (s->IsStagnant())
            s = species.erase(s);
        else
            ++s;
    }
}

void NeuralNetworkTrainer::FillOrganismIntoSpecies(Organism&& organism) {
    bool isCompatibleWithExistingSpecies = false;
    for (auto& currSpecies : species) {
        if (currSpecies.IsCompatible(organism.GetGenome())) {
            currSpecies.AddOrganism(std::move(organism));
            isCompatibleWithExistingSpecies = true;
            break;
        }
    }
    if (!isCompatibleWithExistingSpecies) {
        Species newSpecies(std::move(organism));
        species.push_back(std::move(newSpecies));
    }
    
}

void NeuralNetworkTrainer::DeleteEmptySpecies() {
    species.erase(
        std::remove_if(species.begin(), species.end(), [](const Species& s) {return s.IsEmpty(); }),
        species.end()
    );
}

void NeuralNetworkTrainer::Repopulate() {
    PrepareSpeciesForPopulation();
	auto DidChanceOccure = [](float chance) {
		auto num = rand() % 100;
		return num < int(100.0f * chance);
	};

	for (auto& trainer : bodies) {
		Species* sp = &SelectSpeciesToBreed();
		auto & father = sp->GetOrganismToBreed();
		if (DidChanceOccure(parameters.advanced.reproduction.chanceForInterspecialReproduction)){
			sp = &SelectSpeciesToBreed();
		}
		auto & mother = sp->GetOrganismToBreed();
		auto childNeuralNetwork = father.BreedWith(mother);
		Organism child(&*trainer, std::move(childNeuralNetwork));
        FillOrganismIntoSpecies(std::move(child));
	}
    DeleteEmptySpecies();
	ResetPopulationToTeachableState();
	// TODO jnf Add Concurrency
}

Species& NeuralNetworkTrainer::SelectSpeciesToBreed() {
	// TODO jnf: Switch to stochastic universal sampling
    if (species.size() == 1) {
        return species.front();
    }
    double totalSpeciesFitness = 0.0;
	for (auto& s : species) {
		totalSpeciesFitness += s.GetFittestOrganism().GetOrCalculateFitness();
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