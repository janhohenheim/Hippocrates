#include "gene_examinator.h"
#include <algorithm>

size_t GeneExaminator::GetNumberOfNeuronsInGenes(const std::vector<Gene>& genes)
{
	auto CompareToNeuron = [](const Gene& lhs, const Gene& rhs) {
		return lhs.to < rhs.to;
	};
	auto maxNeuronGene = std::max_element(genes.begin(), genes.end(), CompareToNeuron);
	// TODO jnf
	// Maybe add lookup table
	return maxNeuronGene->to + 1U;
}