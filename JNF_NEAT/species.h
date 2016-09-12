#pragma once
#include "training_parameters.h"
#include "organism.h"
#include <memory>
#include <functional>

namespace JNF_NEAT {

class Species {
private:
	std::vector<std::unique_ptr<Organism>> population;
	std::unique_ptr<Organism> representative;
	bool isSortedByFitness = false;
	std::size_t numberOfStagnantGenerations = 0;
	double fitnessHighscore = 0;
	const TrainingParameters& parameters;

public:
	explicit Species(Organism representative);
	Species(const Species& other) = default;
	Species(Species&& other) = default;
	~Species() = default;

	auto operator=(Species&& other) -> Species&;

	auto AddOrganism(Organism&& organism) -> void;
	auto AnalyzePopulation() -> void;

	auto IsCompatible(const Genome& genome) const -> bool;
	auto IsEmpty() const -> bool { return population.empty(); }
	auto IsStagnant() const -> bool;

	auto LetPopulationLive() -> void;

	auto ResetToTeachableState() -> void;
	auto SetPopulationsFitnessModifier() -> void;
	auto ClearPopulation() -> void;

	auto GetFittestOrganism() -> Organism&;
	auto GetOrganismToBreed() -> Organism&;
	auto GetJSON() const->std::string;



private:
	auto ElectRepresentative() -> void;
	auto SelectRandomRepresentative() -> void;
	auto SelectFittestOrganismAsRepresentative() -> void;

	template <class T>
	constexpr auto IsAboveCompatibilityThreshold(T t) const -> bool {
		return t > representative->GetTrainingParameters().
			
			speciation.
			compatibilityThreshold;
	};
};

}
