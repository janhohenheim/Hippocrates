#include <algorithm>
#include <stdexcept>
#include "../Headers/neural_network_trainer.h"

using namespace JNF_NEAT;
using namespace std;

NeuralNetworkTrainer::NeuralNetworkTrainer(vector<shared_ptr<IBody>> population, TrainingParameters parameters) :
	parameters(move(parameters)),
	populationSize(population.size()),
	bodies(move(population))
{
	CreateInitialOrganisms();
}

auto NeuralNetworkTrainer::TrainUntilFitnessEquals(double fitnessToReach) -> void {
	if (loggingEnabled) {
		logger.CreateLoggingDirs();
	}
	LetGenerationLive();
	while (GetFittestOrganism().GetOrCalculateRawFitness() < (fitnessToReach - 1e-6)) {
		TrainGenerationAndLog();
	}
}

auto NeuralNetworkTrainer::TrainUntilGenerationEquals(size_t generationsToTrain) -> void {
	if (loggingEnabled) {
		logger.CreateLoggingDirs();
	}
	generationsToTrain += generationsPassed;
	LetGenerationLive();
	while (generationsPassed < generationsToTrain) {
		TrainGenerationAndLog();
	}
}

auto NeuralNetworkTrainer::GetTrainedNeuralNetwork() -> TrainedNeuralNetwork {
	return TrainedNeuralNetwork(GetFittestOrganism().GetGenome());
}

auto NeuralNetworkTrainer::CreateInitialOrganisms() -> void {
	for (auto currTrainer : bodies) {
		Genome standardGenes(currTrainer->GetInputCount(), currTrainer->GetOutputCount(), parameters);
		NeuralNetwork network(std::move(standardGenes));
		Organism organism(currTrainer, move(network));
		FillOrganismIntoSpecies(move(organism));
	}
}

auto NeuralNetworkTrainer::TrainGenerationAndLog() -> void {
	Repopulate();
	LetGenerationLive();
	generationsPassed++;
	if (loggingEnabled) {
		logger.LogGeneration(generationsPassed, GetJSON());
	}
}

auto NeuralNetworkTrainer::GetFittestOrganism() -> Organism& {
	if (species.empty()) {
		throw out_of_range("Your population is empty");
	}
	SortSpeciesIfNeeded();
	return species.front().GetFittestOrganism();
}

auto JNF_NEAT::NeuralNetworkTrainer::SortSpeciesIfNeeded() -> void {
	if (!areSpeciesSortedByFitness) {
		auto CompareSpecies = [&](Species& lhs, Species& rhs) {
			return lhs.GetFittestOrganism().GetOrCalculateFitness() < rhs.GetFittestOrganism().GetOrCalculateFitness();
		};
		sort(species.begin(), species.end(), CompareSpecies);
		areSpeciesSortedByFitness = true;
	}
}

auto NeuralNetworkTrainer::LetGenerationLive() -> void {
	for (auto& sp : species) {
		sp.LetPopulationLive();
	}
	SortSpeciesIfNeeded();
}

auto NeuralNetworkTrainer::FillOrganismIntoSpecies(Organism&& organism) -> void {
	bool isCompatibleWithExistingSpecies = false;
	areSpeciesSortedByFitness = false;

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

auto NeuralNetworkTrainer::AnalyzeSpeciesPopulation() -> void {
	for (auto& currSpecies : species) {
		currSpecies.AnalyzePopulation();
	}
}

auto NeuralNetworkTrainer::DeleteStagnantSpecies() -> void {
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

auto NeuralNetworkTrainer::Repopulate() -> void {
	PrepareSpeciesForPopulation();
	auto DidChanceOccure = [](float chance) {
		auto num = rand() % 1000;
		return num < int(1000.0f * chance);
	};
	std::vector<Organism> newGeneration;
	newGeneration.reserve(populationSize);
	for (auto& body : bodies) {
		Species* sp = &SelectSpeciesToBreed();
		auto& father = sp->GetOrganismToBreed();
		if (DidChanceOccure(parameters.reproduction.chanceForInterspecialReproduction)) {
			sp = &SelectSpeciesToBreed();
		}
		auto& mother = sp->GetOrganismToBreed();
		auto childNeuralNetwork(move(father.BreedWith(mother)));
		newGeneration.emplace_back(body, move(childNeuralNetwork));
	}
	ClearSpeciesPopulation();
	for (auto&& child : newGeneration) {
		FillOrganismIntoSpecies(move(child));
	}
	DeleteEmptySpecies();
	ResetPopulationToTeachableState();
	// TODO jnf Add Concurrency
}

auto NeuralNetworkTrainer::ClearSpeciesPopulation() -> void {
	for (auto& sp : species) {
		sp.ClearPopulation();
	}
}

auto NeuralNetworkTrainer::PrepareSpeciesForPopulation() -> void
{
	AnalyzeSpeciesPopulation();
	DeleteStagnantSpecies();
}

auto NeuralNetworkTrainer::DeleteEmptySpecies() -> void
{
	species.erase(
		remove_if(species.begin(), species.end(), [](const Species& s) {return s.IsEmpty(); }),
		species.end()
		);
}

auto NeuralNetworkTrainer::ResetPopulationToTeachableState() -> void
{
	for (auto& sp : species) {
		sp.ResetToTeachableState();
	}
}

auto NeuralNetworkTrainer::SelectSpeciesToBreed() -> Species& {
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


auto NeuralNetworkTrainer::GetJSON() const -> string {
	string s("{\"populationSize\":");
	s += to_string(populationSize);
	s += ",";
	s += "\"generationsPassed\":";
	s += to_string(generationsPassed);
	s += ",";
	s += "\"species\":[";
	for (size_t i = 0; i < species.size() - 1; ++i) {
		s += species[i].GetJSON();
		s += ",";
	}
	s += species.back().GetJSON();
	s += "]}";
	return s;
}
