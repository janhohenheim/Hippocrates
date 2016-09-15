#include <cmath>
#include "genome.h"
#include <algorithm>

using namespace JNF_NEAT;
using namespace std;

Genome::Genome(std::size_t inputCount, std::size_t outputCount, TrainingParameters parameters) :
	parameters(move(parameters)),
	genes((inputCount + parameters.structure.numberOfBiasNeurons) * outputCount),
	inputCount(inputCount),
	outputCount(outputCount),
	neuronCount(inputCount + parameters.structure.numberOfBiasNeurons + outputCount)
{
	auto currentGene = genes.begin();
	for (auto in = 0U; in < (inputCount + parameters.structure.numberOfBiasNeurons); ++in) {
		for (auto out = 0U; out < outputCount; ++out) {
			currentGene->from = in;
			currentGene->to = out + (inputCount + parameters.structure.numberOfBiasNeurons);
			++currentGene;
		}
	}
}


auto Genome::operator=(const Genome& other) -> Genome& {
	this->genes = other.genes;
	this->neuronCount = other.neuronCount;
	return *this;
}

auto Genome::AppendGene(Gene gene) -> void {
	AdjustNeuronCount(gene);
	genes.push_back(std::move(gene));
}

auto Genome::InsertGeneAt(Gene gene, size_t index) -> void {
	AdjustNeuronCount(gene);
	genes.insert(genes.begin() + index, std::move(gene));
}

auto Genome::GetGeneticalDistanceFrom(const Genome& other) const -> double {
	double totalWeightDifference = 0.0;
	size_t numberOfOverlapingGenes = 0;

	size_t sizeOfSmallerGenome = min(this->GetGeneCount(), other.GetGeneCount());
	auto IsHistoricalMarkingSameAt = [&](size_t i) {
		return this->GetGeneAt(i).historicalMarking == other[i].historicalMarking;
	};

	for (size_t i = 0; i < sizeOfSmallerGenome && IsHistoricalMarkingSameAt(i); ++i) {
		totalWeightDifference += (double)abs(this->GetGeneAt(i).weight - other[i].weight);
		++numberOfOverlapingGenes;
	}

	auto numberOfDisjointGenes = this->GetGeneCount() + other.GetGeneCount() - (size_t)2 * numberOfOverlapingGenes;
	auto sizeOfBiggerGenome = max(this->GetGeneCount(), other.GetGeneCount());
	// TODO jnf: Think how we'll handle the next line
	auto disjointGenesInfluence = (double)numberOfDisjointGenes /* / (double)sizeOfBiggerGenome*/;

	auto averageWeightDifference = totalWeightDifference / (double)numberOfOverlapingGenes;

	disjointGenesInfluence *= (double)parameters.speciation.importanceOfDisjointGenes;
	averageWeightDifference *= (double)parameters.speciation.importanceOfAverageWeightDifference;

	return disjointGenesInfluence + averageWeightDifference;
}

auto Genome::DoesContainGene(const Gene& gene) const -> bool {
	for (auto & g : genes) {
		if (g.from == gene.from && g.to == gene.to && g.isRecursive == gene.isRecursive) {
			return true;
		}
	}
	return false;
}

auto Genome::GetJSON() const -> string {
	string s("{");
	s += "\"parameters\":";
	s += parameters.GetJSON();
	s += ",\"inputCount\":";
	s += std::to_string(inputCount);
	s += ",\"outputCount\":";
	s += std::to_string(outputCount);
	s += ",\"genes\":[";
	for (size_t i = 0; i < genes.size() - 1; ++i) {
		s += genes[i].GetJSON();
		s += ",";
	}
	s += genes.back().GetJSON();
	s += "]";
	s += "}";
	return s;
}

auto Genome::AdjustNeuronCount(const Gene & gene) -> void {
	if (gene.to + 1 > neuronCount) {
		neuronCount = gene.to + 1;
	}
}
