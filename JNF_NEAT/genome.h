#pragma once

#include "gene.h"
#include "training_parameters.h"
#include <vector>

class Genome {
	private:
		const TrainingParameters& parameters;
		std::vector<Gene> genes;

	public:
		Genome() = delete;
		explicit Genome(const TrainingParameters& parameters);
		Genome(const Genome& other) = default;
		Genome(Genome&& other) = default;
		~Genome() = default;

		Genome& operator=(const Genome& other);
		const Gene& operator[](std::size_t index) const { return GetGeneAt(index); }
        Gene& operator[](std::size_t index) { return GetGeneAt(index); }
		const Gene& GetGeneAt(std::size_t index) const { return genes[index]; }
        Gene& GetGeneAt(std::size_t index) { return genes[index]; }
		auto begin() { return genes.begin(); }
		auto begin() const { return genes.begin(); }
		auto end() { return genes.end(); }
		auto end() const { return genes.end(); }

		std::size_t ExtrapolateNeuronCount() const;
		std::size_t GetGeneCount() const;

		void AppendGene(const Gene& gene) {genes.push_back(gene);}
		void AppendGene(Gene&& gene) {genes.push_back(std::move(gene));}

        const TrainingParameters& GetTrainingParameters() const { return parameters; }
		double GetGeneticalDistanceFrom(const Genome& other) const;
};