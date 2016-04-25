#pragma once
#include "training_parameters.h"
#include "neural_network.h"

class Species {
	private:
		const TrainingParameters & parameters;
		std::vector<NeuralNetwork *> population;
		NeuralNetwork representative;
	public:
		Species() = delete;
		explicit Species(const TrainingParameters & parameters);
		Species(const Species & other) = default;
		Species(Species && other) = default;
		~Species() = default;

		void AddIndividual(NeuralNetwork & individual);
		void SetPopulation(std::vector<NeuralNetwork> & population);

		bool IsCompatible(const NeuralNetwork & network) const;
		bool IsCompatible(const std::vector<Gene> & genome) const;

		float GetFitnessSharingModifier() const;

	private:
		double GetGeneticalDistance(const std::vector<Gene> & leftGenome, const std::vector<Gene> & rightGenome) const;
		void ElectRepresentative();
		template<class T>
		constexpr bool IsAboveCompatibilityThreshold(T t) const;
};