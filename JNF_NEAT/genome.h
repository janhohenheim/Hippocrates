#pragma once

#include "gene.h"
#include "training_parameters.h"
#include <vector>

namespace JNF_NEAT {

	class Genome {
		private:
			const TrainingParameters& parameters;
			std::vector<Gene> genes;
			size_t neuronCount = 0U;

		public:
			Genome() = delete;
			explicit Genome(const TrainingParameters& parameters);
			Genome(const Genome& other) = default;
			Genome(Genome&& other) = default;
			~Genome() = default;
			Genome& operator=(const Genome& other);
			Genome& operator=(Genome&& other) = default;

			const Gene& operator[](std::size_t index) const { return GetGeneAt(index); }
			Gene& operator[](std::size_t index) { return GetGeneAt(index); }
			const Gene& GetGeneAt(std::size_t index) const { return genes[index]; }
			Gene& GetGeneAt(std::size_t index) { return genes[index]; }
			auto begin() { return genes.begin(); }
			auto begin() const { return genes.begin(); }
			auto end() { return genes.end(); }
			auto end() const { return genes.end(); }

			std::size_t GetNeuronCount() const { return neuronCount; };
			std::size_t GetGeneCount() const;

			void AppendGene(Gene gene) { AdjustNeuronCount(gene); genes.push_back(std::move(gene)); }
			void InsertGeneAt(Gene gene, size_t index) { AdjustNeuronCount(gene); genes.insert(genes.begin() + index, std::move(gene)); }

			const TrainingParameters& GetTrainingParameters() const { return parameters; }
			double GetGeneticalDistanceFrom(const Genome& other) const;
			bool DoesContainGene(const Gene& gene) const;
			std::string GetJSON() const;
		private:
			inline void AdjustNeuronCount(const Gene& gene) { if (gene.to + 1 > neuronCount) neuronCount = gene.to + 1; }
	};

}