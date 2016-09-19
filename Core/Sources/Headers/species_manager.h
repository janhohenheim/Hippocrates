#pragma once
#include "species.h"

namespace JNF_NEAT {
class Organism;

class SpeciesManager {
private:
	const TrainingParameters& parameters;
	mutable bool areSpeciesSortedByFitness = false;
	std::vector<Species> species;

public:
	using Bodies = std::vector<std::unique_ptr<IBody>>;

	explicit SpeciesManager(const TrainingParameters& parameters) : parameters{ parameters } {}
	auto operator[](std::size_t index) const -> const Species& { return species[index]; }

	auto CreateInitialOrganisms(Bodies& bodies) -> void;
	auto Repopulate(Bodies& bodies) -> void;
	auto GetFittestOrganism() -> const Organism&;

	auto LetGenerationLive() -> void;

	auto GetSpeciesCount() const { return species.size(); }

	auto begin() const { return species.begin(); }
	auto end() const { return species.end(); }

private:
	auto ResetPopulationToTeachableState() -> void;
	auto FillOrganismIntoSpecies(Organism&& organism) -> void;
	auto PrepareSpeciesForPopulation() -> void;
	auto AnalyzeSpeciesPopulation() -> void;
	auto DeleteStagnantSpecies() -> void;
	auto DeleteEmptySpecies() -> void;
	auto SortSpeciesIfNeeded() -> void;
	auto ClearSpeciesPopulation() -> void;
	auto GetSpeciesToBreed() -> Species&;
};


}
