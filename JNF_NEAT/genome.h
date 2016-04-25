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
		Gene& operator[](size_t index) { return genes[index]; }
		auto begin() { return genes.begin(); }
		auto end() { return genes.end(); }
		
		std::size_t ExtrapolateNeuronCount() const;
		std::size_t GetGeneCount() const;
		void MutateGenes();

	private:
		static bool DidChanceOccure(float chance);
		bool ShouldAddNeuron() const { return DidChanceOccure(parameters.advanced.mutation.chanceForNeuralMutation); }
		bool ShouldAddConnection() const { return DidChanceOccure(parameters.advanced.mutation.chanceForConnectionalMutation); }
		bool ShouldMutateWeight() const { return DidChanceOccure(parameters.advanced.mutation.chanceForWeightMutation); }
		void AddRandomNeuron();
		void AddRandomConnection();
		void ShuffleWeights();
		void MutateWeightOfGeneAt(size_t index);
		void PerturbWeightAt(size_t index);
};