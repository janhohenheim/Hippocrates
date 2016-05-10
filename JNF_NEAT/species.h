#pragma once
#include "training_parameters.h"
#include "organism.h"
#include <memory>
#include <functional>

class Species {
	private:
		std::vector<Organism> population;
		Genome* representative = nullptr;

	public:
		Species() = default;
		Species(const Species& other);
		Species(Species&& other);
        Species(const Species&& other) = delete;
        ~Species();

		Species&operator=(Species && other);

		void AddOrganism(const Organism &organism);
		void AddOrganism(Organism &&organism);
        void Clear() { population.clear(); }

		const std::vector<Organism>& GetPopulatin() { return population; }
		bool IsCompatible(const Genome& genome) const;
		void LetPopulationLive();
		void ResetToTeachableState();
		Organism& GetFittestOrganism();

		void SetPopulationsFitnessModifier();

		Organism &GetOrganismToBreed();

private:
		void ElectRepresentative();
        void SelectRandomRepresentative();

		template<class T>
		constexpr bool IsAboveCompatibilityThreshold(T t) const;
};