#pragma once

#include "gene.hpp"
#include "training/parameters.hpp"
#include "type.hpp"

#include <vector>

namespace Hippocrates::Genotype {

class Genome {
private:
	std::vector<Gene> genes;
	std::size_t inputCount = 0U;
	std::size_t outputCount = 0U;
	std::size_t neuronCount = 0U;
	auto ParseGenesJson(std::string json)->std::vector<Gene>;

public:
	explicit Genome(std::size_t inputCount, std::size_t outputCount);
	explicit Genome(std::string json);
	explicit Genome() = default;
	Genome(const Genome& other) = default;
	Genome(Genome&& other) = default;

	~Genome() = default;

	auto operator=(const Genome& other)&->Genome& = default;
	auto operator=(Genome&& other)&->Genome& = default;

	auto operator[](std::size_t index) const -> const Gene& { return GetGeneAt(index); }
	auto operator[](std::size_t index) -> Gene&	{ return GetGeneAt(index); }
	auto GetGeneAt(std::size_t index) const -> const Gene& {return genes[index];}
	auto GetGeneAt(std::size_t index) -> Gene& { return genes[index]; }
	auto begin() { return genes.begin(); }
	auto begin() const { return genes.begin(); }
	auto end() { return genes.end(); }
	auto end() const { return genes.end(); }

	auto GetNeuronCount() const  {return neuronCount; }
	auto GetGeneCount() const {return genes.size(); }
	auto GetInputCount() const {	return inputCount; }
	auto GetOutputCount() const	{ return outputCount; }

	auto AppendGene(Gene gene) -> void;
	auto InsertGeneAt(Gene gene, std::size_t index) -> void;

	auto GetGeneticalDistanceFrom(const Genome& other) const -> Type::connection_weight_t;
	auto DoesContainGene(const Gene& gene) const -> bool;
	auto GetJSON() const->std::string;

private:
	auto AdjustNeuronCount(const Gene& gene) -> void;
};

}
