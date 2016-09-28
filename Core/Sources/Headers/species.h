#pragma once
#include "training_parameters.h"
#include "organism.h"
#include <memory>
#include <functional>

namespace Hippocrates {

class Species {
private:
	mutable std::vector<Organism> population;
	Organism representative;
	mutable bool isSortedByFitness = false;
	std::size_t numberOfStagnantGenerations = 0;
	double fitnessHighscore = 0;
	const TrainingParameters& parameters;

public:
	explicit Species(Organism representative);
	Species(const Species& other) = default;
	Species(Species&& other) = default;
	~Species() = default;

	auto operator=(Species&& other) noexcept -> Species&;

	auto AddOrganism(Organism&& organism) -> void;
	auto AnalyzePopulation() -> void;

	auto IsCompatible(const Genome& genome) const -> bool;
	auto IsEmpty() const -> bool { return population.empty(); }
	auto IsStagnant() const -> bool;

	auto LetPopulationLive() -> void;

	auto ResetToTeachableState() -> void;
	auto SetPopulationsFitnessModifier() -> void;
	auto ClearPopulation() -> void;

	auto GetFittestOrganism() const -> const Organism&;
	auto SortPopulationIfNeeded() const -> void;
	auto GetOrganismToBreed() -> Organism&;
	auto GetJSON() const->std::string;



private:
	auto ElectRepresentative() -> void;
	auto SelectRandomRepresentative() -> void;
	auto SelectFittestOrganismAsRepresentative() -> void;

	template <class T>
	constexpr auto IsAboveCompatibilityThreshold(T t) const -> bool {
		return t > representative.GetTrainingParameters().
			speciation.
			compatibilityThreshold;
	};

	auto UpdateOrganism(Organism &organism) -> void;
	auto UpdateOrganismWithMemoryResets(Organism &organism) -> void;

	auto LetOrganismFinishTask(Organism& organism) -> void;
};

}
