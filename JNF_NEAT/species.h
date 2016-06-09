#pragma once
#include "training_parameters.h"
#include "organism.h"
#include <memory>
#include <functional>

namespace JNF_NEAT {

	class Species {
		private:
			std::vector<Organism*> population;
			std::unique_ptr<Organism> representative;
			bool isSortedByFitness = false;
			size_t numberOfStagnantGenerations = 0;
			size_t fitnessHighscore = 0;
			const TrainingParameters& parameters;

		public:
			Species(const Organism& representative);
			Species(Organism&& representative);
			Species(const Species& other) = default;
			Species(Species&& other) = default;
			~Species();

			Species& operator=(Species&& other);

			void AddOrganism(const Organism& organism);
			void AddOrganism(Organism&& organism);
			void AnalyzeAndClearPopulation();

			bool IsCompatible(const Genome& genome) const;
			bool IsEmpty() const { return population.empty(); }
			bool IsStagnant() const { return (numberOfStagnantGenerations >= parameters.advanced.speciation.stagnantSpeciesClearThreshold); }
			void LetPopulationLive();
			void ResetToTeachableState();
			Organism& GetFittestOrganism();
			void SetPopulationsFitnessModifier();
			Organism& GetOrganismToBreed();

		private:
			void ElectRepresentative();
			void SelectRandomRepresentative();
			void SelectFittestOrganismAsRepresentative();

			template<class T>
			constexpr bool IsAboveCompatibilityThreshold(T t) const;
	};

}