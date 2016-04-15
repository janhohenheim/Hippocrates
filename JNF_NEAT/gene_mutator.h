#pragma once
#include "gene.h"
#include "training_parameters.h"
#include <vector>
#include <algorithm>
class GeneMutator {
	// Members
	private:
		TrainingParameters parameters;

	// Methods
	public:
		GeneMutator() = delete;
		explicit GeneMutator(const TrainingParameters & parameters);
		GeneMutator(const GeneMutator & other) = default;
		GeneMutator(const GeneMutator && other) = delete;

		~GeneMutator() = default;

		void MutateGenes(std::vector<Gene> & genes) const;
	private:
		static bool DidChanceOccure(float chance);
		bool ShouldAddNeuron() const { return DidChanceOccure(parameters.ruleset.chanceForNeuralMutation); }
		bool ShouldAddConnection() const { return DidChanceOccure(parameters.ruleset.chanceForConnectionalMutation); }
		bool ShouldMutateWeight() const { return DidChanceOccure(parameters.ruleset.chanceForWeightMutation); }
		void AddRandomNeuron(std::vector<Gene> & genes) const;
		void AddRandomConnection(std::vector<Gene> & genes) const;
		void ShuffleWeights(std::vector<Gene> & genes) const;
		void MutateWeightOfGene(Gene & gene) const;
		void PerturbWeight(float & weight) const;
};