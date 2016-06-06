#pragma once
#include "training_parameters.h"
#include "organism.h"
#include <memory>
#include <functional>

class Species {
	private:
		std::vector<Organism*> population;
		Genome* representative = nullptr;
		bool isSortedByFitness = false;
        size_t numberOfStagnantGenerations = 0;
        int fitnessHighscore = 0;
        const TrainingParameters& parameters;

	public:
		Species(const Organism& representative);
		Species(Organism&& representative);
		Species(const Species& other);
		Species(Species&& other);
		Species(const Species&& other) = delete;
		~Species();

		Species& operator=(Species&& other);

		void AddOrganism(const Organism& organism);
		void AddOrganism(Organism&& organism);
        void Clear();

		bool IsCompatible(const Genome& genome) const;
		bool IsEmpty() const { return population.empty(); }
        bool IsStagnant() const { return numberOfStagnantGenerations >= parameters.advanced.speciation.stagnantSpeciesClearThreshold; }
		void LetPopulationLive();
		void ResetToTeachableState();
		Organism& GetFittestOrganism();
		void SetPopulationsFitnessModifier();
		Organism& GetOrganismToBreed();

private:
		void ElectRepresentative();
		void SelectRandomRepresentative();

		template<class T>
		constexpr bool IsAboveCompatibilityThreshold(T t) const;
};