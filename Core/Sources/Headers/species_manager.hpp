#pragma once
#include "species.hpp"
#include "innovation_cacher.hpp"

namespace Hippocrates {
class Organism;

class SpeciesManager {
private:
	mutable bool areSpeciesSortedByFitness = false;
	std::vector<Species> species;
	InnovationCacher currGenerationInnovations;

public:
	using Bodies = std::vector<std::reference_wrapper<IBody>>;

	auto operator[](std::size_t index) const -> const Species& { return species[index]; }

	auto CreateInitialOrganisms(Bodies& bodies) -> void;
	auto Repopulate(Bodies& bodies) -> void;
	auto BreedInSpecies(const Species & species) -> NeuralNetwork;
	auto GetFittestSpecies() -> const Species &;
	auto GetFittestOrganism() -> const Organism&;

	auto LetGenerationLive() -> void;

	auto GetSpeciesCount() const { return species.size(); }
	auto GetPopulationCount() const -> std::size_t;
	auto GetTotalFitness() const ->Type::fitness_t;
	auto GetAverageFitness() const ->Type::fitness_t;

	auto begin() const { return species.begin(); }
	auto end() const { return species.end(); }

private:
	auto ResetPopulationToTeachableState() -> void;
	auto FillOrganismIntoSpecies(Organism&& organism) -> void;
	auto DeleteEmptySpecies() -> void;
	auto SortSpeciesIfNeeded() -> void;
	auto ClearSpeciesPopulation() -> void;
};


}
