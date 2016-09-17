#include "species_manager.h"
#include <algorithm>
using namespace JNF_NEAT;

auto SpeciesManager::CreateInitialOrganisms(const Bodies& bodies) -> void {
	for (auto currTrainer : bodies) {
		Genome standardGenes(currTrainer->GetInputCount(), currTrainer->GetOutputCount(), parameters);
		NeuralNetwork network(std::move(standardGenes));
		Organism organism(currTrainer, std::move(network));
		FillOrganismIntoSpecies(std::move(organism));
	}
}

auto SpeciesManager::Repopulate(const Bodies& bodies) -> void {
	PrepareSpeciesForPopulation();
	auto DidChanceOccure = [](float chance) {
		auto num = rand() % 1000;
		return num < int(1000.0f * chance);
	};
	std::vector<Organism> newGeneration;
	newGeneration.reserve(bodies.size());
	for (auto& body : bodies) {
		auto sp = &GetSpeciesToBreed();
		auto& father = sp->GetOrganismToBreed();
		if (DidChanceOccure(parameters.reproduction.chanceForInterspecialReproduction)) {
			sp = &GetSpeciesToBreed();
		}
		auto& mother = sp->GetOrganismToBreed();
		auto childNeuralNetwork(std::move(father.BreedWith(mother)));
		newGeneration.emplace_back(body, std::move(childNeuralNetwork));
	}
	ClearSpeciesPopulation();
	for (auto&& child : newGeneration) {
		FillOrganismIntoSpecies(std::move(child));
	}
	DeleteEmptySpecies();
}

auto SpeciesManager::DeleteEmptySpecies() -> void {
	species.erase(
		std::remove_if(species.begin(), species.end(), [](const Species& s) {return s.IsEmpty(); }),
		species.end()
	);
}

auto SpeciesManager::FillOrganismIntoSpecies(Organism&& organism) -> void {
	areSpeciesSortedByFitness = false;
	auto isCompatibleWithExistingSpecies = false;
	

	for (auto& currSpecies : species) {
		if (currSpecies.IsCompatible(organism.GetGenome())) {
			currSpecies.AddOrganism(std::move(organism));
			isCompatibleWithExistingSpecies = true;
			break;
		}
	}
	if (!isCompatibleWithExistingSpecies) {
		species.emplace_back(std::move(organism));
	}
}

auto SpeciesManager::PrepareSpeciesForPopulation() -> void {
	AnalyzeSpeciesPopulation();
	DeleteStagnantSpecies();
}

auto SpeciesManager::AnalyzeSpeciesPopulation() -> void {
	for (auto& currSpecies : species) {
		currSpecies.AnalyzePopulation();
	}
}

auto SpeciesManager::DeleteStagnantSpecies() -> void {
	auto IsStagnant = [](const Species& species) {
		return species.IsStagnant();
	};
	auto removePos = remove_if(species.begin(), species.end(), IsStagnant);
	// Let at least one species survive
	if (!species.empty() && removePos == species.begin()) {
		++removePos;
	}
	species.erase(removePos, species.end());
}

auto SpeciesManager::ClearSpeciesPopulation() -> void {
	for (auto& sp : species) {
		sp.ClearPopulation();
	}
}

auto SpeciesManager::GetSpeciesToBreed() -> Species& {
	// TODO jnf: Switch to stochastic universal sampling
	if (species.empty()) {
		throw std::out_of_range("There are no species");
	}
	auto totalSpeciesFitness = 0.0;
	for (const auto& s : species) {
		totalSpeciesFitness += s.GetFittestOrganism().GetOrCalculateFitness();
	}
	if (totalSpeciesFitness == 0) {
		return species[rand() % species.size()];
	}
	auto chance = 0.0;
	auto GetChanceForSpecies = [&chance, &totalSpeciesFitness](const Species& species) {
		return chance + (species.GetFittestOrganism().GetOrCalculateFitness() / totalSpeciesFitness);
	};
	while (true) {
		for (auto& s : species) {
			auto randNum = static_cast<double>(rand() % 10'000) / 9'999.0;
			chance = GetChanceForSpecies(s);
			if (randNum < chance) {
				return s;
			}
		}
	}
}

auto SpeciesManager::GetFittestOrganism() -> const Organism& {
	if (species.empty()) {
		throw std::out_of_range("Your population is empty");
	}
	SortSpeciesIfNeeded();
	return species.front().GetFittestOrganism();
}

auto SpeciesManager::SortSpeciesIfNeeded() -> void {
	if (!areSpeciesSortedByFitness) {
		auto CompareSpecies = [](const Species& lhs, const Species& rhs) {
			return lhs.GetFittestOrganism().GetOrCalculateFitness() < rhs.GetFittestOrganism().GetOrCalculateFitness();
		};
		std::sort(species.begin(), species.end(), CompareSpecies);
		areSpeciesSortedByFitness = true;
	}
}

auto SpeciesManager::LetGenerationLive() -> void {
	ResetPopulationToTeachableState();
	for (auto& sp : species) {
		sp.LetPopulationLive();
	}
	areSpeciesSortedByFitness = false;
}

auto SpeciesManager::ResetPopulationToTeachableState() -> void {
	for (auto& sp : species) {
		sp.ResetToTeachableState();
	}
}
