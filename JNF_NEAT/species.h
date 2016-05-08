#pragma once
#include "training_parameters.h"
#include "genome.h"
#include <memory>
#include <functional>

class Species {
	private:
		std::vector<std::reference_wrapper<const Genome>> population;
		Genome* representative = nullptr;

	public:
		Species() = default;
		Species(const Species& other);
		Species(Species&& other);
        Species(const Species&& other) = delete;
        ~Species();


		void AddIndividual(const Genome& individual);
        void Clear() { population.clear(); }

		bool IsCompatible(const Genome& genome) const;

		float GetFitnessSharingModifier() const;

	private:
		void ElectRepresentative();
        void SelectRandomRepresentative();

		template<class T>
		constexpr bool IsAboveCompatibilityThreshold(T t) const;
};