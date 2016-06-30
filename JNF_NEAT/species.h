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
			size_t numberOfStagnantGenerations = 0;
			double fitnessHighscore = 0;
			const TrainingParameters& parameters;

		public:
			explicit Species(Organism representative);
			Species(const Species& other) = default;
			Species(Species&& other) = default;
			~Species() = default;
			Species& operator=(Species&& other);

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
			std::string GetJSON() const;

		private:
			void ElectRepresentative();
			void SelectRandomRepresentative();
			void SelectFittestOrganismAsRepresentative();

			template <class T>
			inline constexpr bool IsAboveCompatibilityThreshold(T t) const {
				return t > representative->GetTrainingParameters().advanced.speciation.compatibilityThreshold;
			};
	};

}