#pragma once
#include "training_parameters.h"
#include "neural_network.h"
#include <memory>

class Species {
	private:
		const TrainingParameters& parameters;
		std::vector<NeuralNetwork*> population;
		NeuralNetwork* representative = nullptr;

	public:
		Species() = delete;
		explicit Species(const TrainingParameters& parameters);
		Species(const Species& other);
		Species(Species&& other);
        Species(const Species&& other) = delete;
        ~Species();

		void AddIndividual(NeuralNetwork& individual);
		void SetPopulation(std::vector<NeuralNetwork>& population);

		bool IsCompatible(const NeuralNetwork& network) const;
		bool IsCompatible(const Genome& genome) const;

		float GetFitnessSharingModifier() const;

	private:
		double GetGeneticalDistance(const Genome& leftGenome, const Genome& rightGenome) const;
		void ElectRepresentative();
        void DeleteRepresentative();
        void SelectRandomRepresentative();

		template<class T>
		constexpr bool IsAboveCompatibilityThreshold(T t) const;
};