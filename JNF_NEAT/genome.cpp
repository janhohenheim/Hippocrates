#include "genome.h"
#include <vector>
#include <algorithm>

Genome::Genome(const TrainingParameters& parameters) :
	parameters(parameters)
{
}

std::size_t Genome::ExtrapolateNeuronCount() const {
	auto CompareToNeuron = [](const Gene& lhs, const Gene& rhs) {
		return lhs.to < rhs.to;
	};
	auto maxNeuronGene = std::max_element(genes.begin(), genes.end(), CompareToNeuron);
	// TODO jnf
	// Maybe add lookup table
	return maxNeuronGene->to + 1U;
}

std::size_t Genome::GetGeneCount() const {
	return genes.size();
}

Genome& Genome::operator=(const Genome & other)
{
	this->genes = other.genes; 
	const_cast<TrainingParameters&>(this->parameters) = other.parameters;
	return *this;
}

void Genome::MutateGenes() {
	if (ShouldAddConnection()) {
		AddRandomConnection();
	}
	else
	if (ShouldAddNeuron()) {
		AddRandomNeuron();
	}
	else {
		ShuffleWeights();
	}
}

bool Genome::DidChanceOccure(float chance)
{
	auto num = rand() % 100;
	return num < int(100.0f * chance);
}

void Genome::AddRandomNeuron()
{
	Gene * randGene = nullptr;
	do {
		int num = rand() % genes.size();
		randGene = &genes[num];
	} while (!randGene->isEnabled);

	auto numberOfNeurons = ExtrapolateNeuronCount();

	Gene g1(*randGene);
	g1.to = numberOfNeurons;
	genes.push_back(std::move(g1));

	Gene g2(*randGene);
	g2.from = numberOfNeurons;
	genes.push_back(std::move(g2));

	randGene->isEnabled = false;
}

void Genome::AddRandomConnection()
{
	auto GetRandomNumberBetween = [](size_t min, size_t max) {
		return rand() % (max - min) + min;
	};

	Gene newConnection;
	auto numberOfNeurons = ExtrapolateNeuronCount() - 1U;

	newConnection.from = GetRandomNumberBetween(0U, numberOfNeurons - 1U);
	newConnection.to = GetRandomNumberBetween(newConnection.from + 1, numberOfNeurons);

	genes.push_back(newConnection);
}

void Genome::ShuffleWeights()
{
	for (size_t i = 0; i < genes.size(); i++) {
		if (ShouldMutateWeight()) {
			MutateWeightOfGeneAt(i);
		}
	}
}

void Genome::MutateWeightOfGeneAt(size_t index)
{
	constexpr float chanceOfTotalWeightReset = 0.1f;
	if (DidChanceOccure(chanceOfTotalWeightReset)) {
		genes[index].SetRandomWeight();
	}
	else {
		PerturbWeightAt(index);
	}
}

void Genome::PerturbWeightAt(size_t index)
{
	constexpr float perturbanceBoundaries = 0.2f;
	auto perturbance = (float)(rand() % 10'000) / 10'000.0f * perturbanceBoundaries;
	if (rand() % 2) {
		perturbance = -perturbance;
	}

	genes[index].weight *= perturbance;
}

