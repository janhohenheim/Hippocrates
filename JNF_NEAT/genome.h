#pragma once

#include "gene.h"
#include "training_parameters.h"
#include <vector>

class Genome {
	// Members
	private:
		std::vector<Gene> genes;
		const TrainingParameters& parameters;

	// Methods
	public:
		Genome() = delete;
		explicit Genome(const TrainingParameters& parameters);
		Genome(const Genome& other) = default;
		Genome(Genome&& other) = default;
		~Genome() = default;

		Genome& operator=(const Genome& other);
		const Gene& operator[](std::size_t index) const { return GetGeneAt(index); }
		const Gene& GetGeneAt(std::size_t index) const { return genes[index]; }
		auto begin() { return genes.begin(); }
		auto begin() const { return genes.begin(); }
		auto end() { return genes.end(); }
		auto end() const { return genes.end(); }

		std::size_t ExtrapolateNeuronCount() const;
		std::size_t GetGeneCount() const;
		void MutateGenes();
		double GetGeneticalDistanceFrom(const Genome& other) const;

	private:
		static bool DidChanceOccure(float chance);
		bool ShouldAddNeuron() const { return DidChanceOccure(parameters.advanced.mutation.chanceForNeuralMutation); }
		bool ShouldAddConnection() const { return DidChanceOccure(parameters.advanced.mutation.chanceForConnectionalMutation); }
		bool ShouldMutateWeight() const { return DidChanceOccure(parameters.advanced.mutation.chanceForWeightMutation); }
		void AddRandomNeuron();
		void AddRandomConnection();
		void ShuffleWeights();
		void MutateWeightOfGeneAt(std::size_t index);
		void PerturbWeightAt(std::size_t index);
};