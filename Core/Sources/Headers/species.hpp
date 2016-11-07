#pragma once
#include "training_parameters.hpp"
#include "organism.hpp"
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
	auto GetTrainingParameters() const -> const TrainingParameters& { return representative.GetTrainingParameters(); };

public:
	explicit Species(Organism representative);
	Species(const Species& other) = default;
	Species(Species&& other) = default;
	~Species() = default;

	auto operator=(Species&& other) noexcept -> Species&;

	auto AddOrganism(Organism&& organism) -> void;
	auto AnalyzePopulation() -> void;

	auto IsCompatible(const Genome& genome) const -> bool;
	auto GetSize() const { return population.size(); }
	auto IsEmpty() const { return population.empty(); }
	auto GetAverageFitness() const -> double;
	auto GetTotalFitness() const -> double;
	auto IsStagnant() const -> bool;
	auto GetOffspringCount(double averageFitness) const -> std::size_t;

	auto LetPopulationLive() -> void;

	auto ResetToTeachableState() -> void;
	auto SetPopulationsFitnessModifier() -> void;
	auto ClearPopulation() -> void;
	auto RemoveWorst() { population.pop_back(); }

	auto GetFittestOrganism() const -> const Organism&;
	auto SortPopulationIfNeeded() const -> void;
	auto GetOrganismToBreed() const -> const Organism&;
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
};

}
