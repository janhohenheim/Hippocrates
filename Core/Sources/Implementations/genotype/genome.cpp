#include <cmath>
#include <algorithm>
#include <iostream>

#include "genotype/genome.hpp"
#include "utility/jsmn.h"

using namespace Hippocrates;
using namespace Hippocrates::Genotype;

Genome::Genome(std::size_t inputCount, std::size_t outputCount) :
	genes((inputCount + Training::GetParameters().structure.numberOfBiasNeurons) * outputCount),
	inputCount(inputCount),
	outputCount(outputCount),
	neuronCount(inputCount + Training::GetParameters().structure.numberOfBiasNeurons + outputCount)
{
	auto currentGene = genes.begin();
	for (auto in = 0U; in < (inputCount + Training::GetParameters().structure.numberOfBiasNeurons); ++in) {
		for (auto out = 0U; out < outputCount; ++out) {
			currentGene->from = in;
			currentGene->to = out + (inputCount + Training::GetParameters().structure.numberOfBiasNeurons);
			++currentGene;
		}
	}
}

Genome::Genome(const std::string& json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	std::size_t token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (std::size_t i = 0; i < token_count - 1; i++) {
		auto key = json.substr(tokens[i].start, tokens[i].end - tokens[i].start);
		auto value = json.substr(tokens[i+1].start, tokens[i+1].end - tokens[i+1].start);

		if (key == "inputCount") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &inputCount);
		} else
		if (key == "outputCount") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &outputCount);
		} else
		if (key == "neuronCount") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &neuronCount);
		} else
		if (key == "genes") {
			genes = ParseGenesJson(value);
		}
	}
}

auto Genome::AppendGene(Gene gene) -> void {
	AdjustNeuronCount(gene);
	genes.push_back(std::move(gene));
}

auto Genome::InsertGeneAt(Gene gene, std::size_t index) -> void {
	AdjustNeuronCount(gene);
	genes.insert(genes.begin() + index, std::move(gene));
}

auto Genome::GetGeneticalDistanceFrom(const Genome& other) const -> Type::connection_weight_t {
	Type::connection_weight_t totalWeightDifference = 0.0;
	size_t numberOfOverlapingGenes = 0;

	size_t sizeOfSmallerGenome = std::min(this->GetGeneCount(), other.GetGeneCount());
	auto IsHistoricalMarkingSameAt = [&](std::size_t i) {
		return this->GetGeneAt(i).historicalMarking == other[i].historicalMarking;
	};

	for (std::size_t i = 0; i < sizeOfSmallerGenome && IsHistoricalMarkingSameAt(i); ++i) {
		totalWeightDifference += (Type::connection_weight_t)abs(this->GetGeneAt(i).weight - other[i].weight);
		++numberOfOverlapingGenes;
	}

	auto numberOfDisjointGenes = this->GetGeneCount() + other.GetGeneCount() - (std::size_t)2 * numberOfOverlapingGenes;
	// the next line doesn't normalize by dividing through the size of the bigger genome
	// because stanley's original implementation does it this way, 
	// despite it not being strictly conform to his paper.
	// It makes more sense this way though (see http://sharpneat.sourceforge.net/research/speciation-canonical-neat.html)
	auto disjointGenesInfluence = (Type::connection_weight_t)numberOfDisjointGenes;

	auto averageWeightDifference = totalWeightDifference / (Type::connection_weight_t)numberOfOverlapingGenes;

	disjointGenesInfluence *= (Type::connection_weight_t)Training::GetParameters().speciation.importanceOfDisjointGenes;
	averageWeightDifference *= (Type::connection_weight_t)Training::GetParameters().speciation.importanceOfAverageWeightDifference;

	return disjointGenesInfluence + averageWeightDifference;
}

auto Genome::DoesContainGene(const Gene& gene) const -> bool {
	return std::find(begin(), end(), gene) != end();
}

auto Genome::GetJSON() const -> std::string {
	std::string s("{");
	s += ",\"inputCount\":";
	s += std::to_string(inputCount);
	s += ",\"outputCount\":";
	s += std::to_string(outputCount);
	s += ",\"neuronCount\":";
	s += std::to_string(neuronCount);
	s += ",\"genes\":[";
	for (std::size_t i = 0; i < genes.size() - 1; ++i) {
		s += genes[i].GetJSON();
		s += ",";
	}
	s += genes.back().GetJSON();
	s += "]";
	s += "}";
	return s;
}

auto Genome::ParseGenesJson(const std::string& json) -> std::vector<Gene> {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	std::size_t token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	std::vector<Gene> genes;

	for (std::size_t i = 0; i < token_count - 1; i++) {
		if (tokens[i].type == JSMN_OBJECT) {
			genes.push_back(Gene(json.substr(tokens[i].start, tokens[i].end - tokens[i].start)));
		}
	}

	return genes;
}

auto Genome::AdjustNeuronCount(const Gene & gene) -> void {
	if (gene.to + 1 > neuronCount) {
		neuronCount = gene.to + 1;
	}
}
