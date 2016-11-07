#include "../Headers/species_manager.hpp"
#include <algorithm>
using namespace Hippocrates;

auto SpeciesManager::CreateInitialOrganisms(Bodies& bodies) -> void {
	for (auto& currTrainer : bodies) {
		Genome standardGenes(currTrainer.get().GetInputCount(), currTrainer.get().GetOutputCount(), parameters);
		NeuralNetwork network(std::move(standardGenes));
		Organism organism(currTrainer, std::move(network));
		FillOrganismIntoSpecies(std::move(organism));
	}
}

auto SpeciesManager::Repopulate(Bodies& bodies) -> void {
	auto populationCount = GetPopulationCount();
	auto averageFitness = GetAverageFitness();
	
	std::vector<Organism> newGeneration;
	newGeneration.reserve(bodies.size());

	auto currBody = bodies.begin();
	auto Breed = [this, &newGeneration, &currBody](const auto & species) {
		auto child = BreedInSpecies(species);
		newGeneration.emplace_back(*currBody, std::move(child));
		++currBody;
	};

	auto CloneChamp = [this, &newGeneration, &currBody](const auto & species) {
		auto& champ = species.GetFittestOrganism();
		auto champNetwork = champ.GetNeuralNetwork();
		newGeneration.emplace_back(*currBody, std::move(champNetwork));
		++currBody;
	};

	
	PrepareSpeciesForPopulation();
	// In the original implementation the offspring were tossed directly into their new species and, as a result, in the mating pool.
	// We instead separate the generations
	for (auto& s : species) {
		auto offspringCount = s.GetOffspringCount(averageFitness);
		offspringCount = std::min(offspringCount, s.GetSize());
		s.RemoveWorst();

		if (offspringCount >= 1 
		&&	s.GetSize() > parameters.reproduction.minSpeciesSizeForChampConservation) {
			CloneChamp(s);
			offspringCount--;
		}

		for (std::size_t i = 0; i < offspringCount; ++i) {
			Breed(s);
		}
	}

	// Account for rounding Errors
	while (newGeneration.size() < populationCount) {
		Breed(GetFittestSpecies());
	}


	ClearSpeciesPopulation();
	for (auto&& child : newGeneration) {
		FillOrganismIntoSpecies(std::move(child));
	}
	DeleteEmptySpecies();
}

auto SpeciesManager::BreedInSpecies(const Species& species) const -> NeuralNetwork {
	const auto& mother = species.GetOrganismToBreed();

	// Note that the father can be the same as the mother
	const Organism* father = nullptr;
	if (Utility::DidChanceOccure(parameters.reproduction.chanceForInterspecialReproduction))
		father = &Utility::GetRandomElement(this->species)->GetFittestOrganism();
	else
		father = &species.GetOrganismToBreed();

	return father->BreedWith(mother);
}

auto SpeciesManager::GetFittestSpecies() -> const Species & {
	if (species.empty()) {
		throw std::out_of_range("Your population is empty");
	}
	SortSpeciesIfNeeded();
	return species.front();
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
	for (auto& sp : species)
		sp.ClearPopulation();
}

auto SpeciesManager::GetAverageFitness() const -> double {
	return GetTotalFitness() / GetPopulationCount();
}

auto SpeciesManager::GetPopulationCount() const -> std::size_t {
	std::size_t populationCount = 0;
	for (const auto & s : species)
		populationCount += s.GetSize();
	return populationCount;
}

auto SpeciesManager::GetTotalFitness() const -> double {
	auto totalFitness = 0.0;
	for (auto & s : species)
		totalFitness += s.GetTotalFitness();
	return totalFitness;
}

auto SpeciesManager::GetFittestOrganism() -> const Organism& {
	return GetFittestSpecies().GetFittestOrganism();
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
	for (auto& sp : species) 
		sp.LetPopulationLive();
	areSpeciesSortedByFitness = false;
}

auto SpeciesManager::ResetPopulationToTeachableState() -> void {
	for (auto& sp : species) 
		sp.ResetToTeachableState();
}
