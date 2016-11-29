#pragma once
#include "phenotype/organism.hpp"
#include <memory>
#include <functional>

namespace Hippocrates::Training {

class Species {
private:
	mutable std::vector<Phenotype::Organism> population;
	Phenotype::Organism representative;
	mutable bool isSortedByFitness = false;
	std::size_t numberOfStagnantGenerations = 0;
	Type::fitness_t fitnessHighscore = 0;

public:
	explicit Species(Phenotype::Organism representative);
	Species(const Species& other) = default;
	Species(Species&& other) = default;
	~Species() = default;

	auto operator=(Species& other) & -> Species& = default;
	auto operator=(Species&& other) & -> Species& = default;

	auto AddOrganism(Phenotype::Organism&& organism) -> void;

	auto IsCompatible(const Genotype::Genome& genome) const -> bool;
	auto GetSize() const { return population.size(); }
	auto IsEmpty() const { return population.empty(); }
	auto GetAverageFitness() const -> Type::fitness_t;
	auto GetTotalFitness() const -> Type::fitness_t;
	auto IsStagnant() const -> bool;
	auto GetOffspringCount(Type::fitness_t averageFitness) const -> std::size_t;

	auto LetPopulationLive() -> void;

	auto ResetToTeachableState() -> void;
	auto SetPopulationsFitnessModifier() -> void;
	auto ClearPopulation() -> void;
	auto RemoveWorst() -> void;

	auto GetFittestOrganism() const -> const Phenotype::Organism&;
	auto SortPopulationIfNeeded() const -> void;
	auto GetOrganismToBreed() const -> const Phenotype::Organism&;
	auto GetJSON() const->std::string;

private:
	auto ElectRepresentative() -> void;
	auto SelectRandomRepresentative() -> void;
	auto SelectFittestOrganismAsRepresentative() -> void;

	template <class T>
	constexpr auto IsAboveCompatibilityThreshold(T t) const -> bool {
		return t > GetParameters().
			speciation.
			compatibilityThreshold;
	};
};

}
