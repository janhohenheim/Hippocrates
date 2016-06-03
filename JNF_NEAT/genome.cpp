#include "genome.h"
#include <algorithm>

Genome::Genome(const TrainingParameters& parameters) :
    parameters(parameters),
	genes((parameters.numberOfInputs + parameters.advanced.structure.numberOfBiasNeurons) * parameters.numberOfOutputs),
	neuronCount((parameters.numberOfInputs + parameters.advanced.structure.numberOfBiasNeurons) + parameters.numberOfOutputs)
{
	auto *currentGene = &genes.front();
	for (auto in = 0U; in < (parameters.numberOfInputs + parameters.advanced.structure.numberOfBiasNeurons); ++in) {
		for (auto out = 0U; out < parameters.numberOfOutputs; ++out) {
			currentGene->from = in;
			currentGene->to = out + (parameters.numberOfInputs + parameters.advanced.structure.numberOfBiasNeurons);
			++currentGene;
		}
	}
}

std::size_t Genome::GetGeneCount() const {
	return genes.size();
}

Genome& Genome::operator=(const Genome& other) {
	this->genes = other.genes; 
	this->neuronCount = other.neuronCount;
	const_cast<TrainingParameters&>(this->parameters) = other.parameters;
	return *this;
}


double Genome::GetGeneticalDistanceFrom(const Genome& other) const {
	double totalWeightDifference = 0.0;
	size_t numberOfOverlapingGenes = 0;

	size_t sizeOfSmallerGenome = std::min(this->GetGeneCount(), other.GetGeneCount());
	auto IsHistoricalMarkingSameAt = [&](size_t i) {
		return this->GetGeneAt(i).historicalMarking == other[i].historicalMarking;
	};

	for (size_t i = 0; i < sizeOfSmallerGenome && IsHistoricalMarkingSameAt(i); ++i) {
		totalWeightDifference += (double)std::abs(this->GetGeneAt(i).weight - other[i].weight);
		++numberOfOverlapingGenes;
	}

	auto numberOfDisjointGenes = this->GetGeneCount() + other.GetGeneCount() - (size_t)2 * numberOfOverlapingGenes;
	auto sizeOfBiggerGenome = std::max(this->GetGeneCount(), other.GetGeneCount());
    // TODO jnf: Think how we'll handle the next line
	auto disjointGenesInfluence = (double)numberOfDisjointGenes /* / (double)sizeOfBiggerGenome*/;

	auto averageWeightDifference = totalWeightDifference / (double)numberOfOverlapingGenes;

	disjointGenesInfluence *= (double)parameters.advanced.speciation.importanceOfDisjointGenes;
	averageWeightDifference *= (double)parameters.advanced.speciation.importanceOfAverageWeightDifference;

	return disjointGenesInfluence + averageWeightDifference;
}

bool Genome::DoesContainGene(const Gene & gene) const {
	for (auto & g : genes) {
		if (g.from == gene.from && g.to == gene.to) {
			return true;
		}
	}
	return false;
}