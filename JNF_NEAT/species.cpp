#include "species.h"
#include <algorithm>

Species::Species(const TrainingParameters& parameters) :
	parameters(parameters)
{
}

void Species::AddIndividual(NeuralNetwork& individual)
{
	population.push_back(&individual);
	ElectRepresentative();
}

void Species::SetPopulation(std::vector<NeuralNetwork>& population)
{
	this->population.empty();
	this->population.reserve(population.size());
	for (auto& individual : population) {
		this->population.push_back(&individual);
	}
	ElectRepresentative();
}

bool Species::IsCompatible(const NeuralNetwork& network) const {
	return IsCompatible(network.GetGenome());
}

bool Species::IsCompatible(const Genome& genome) const {
	auto distanceToSpecies = GetGeneticalDistance(representative->GetGenome(), genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

float Species::GetFitnessSharingModifier() const{
	unsigned int fitnessSharingDivisor = 0;

	for (auto& lhs : population) {
		for (auto& rhs : population) {
			auto distance = GetGeneticalDistance(lhs->GetGenome(), rhs->GetGenome());
			if (IsAboveCompatibilityThreshold(distance)) {
				++fitnessSharingDivisor;
			}
		}
	}

	float fitnessSharingFactor = 1.0f / (float) fitnessSharingDivisor;
	return fitnessSharingFactor;
}

double Species::GetGeneticalDistance(const Genome& leftGenome, const Genome& rightGenome) const
{
	double totalWeightDifference = 0.0;
	size_t numberOfOverlapingGenes = 0;

	size_t sizeOfSmallerGenome = std::min(leftGenome.GetGeneCount(), rightGenome.GetGeneCount());
	auto IsHistoricalMarkingSameAt = [&](size_t i) {
		return const_cast<Genome&>(leftGenome)[i].historicalMarking == const_cast<Genome&>(rightGenome)[i].historicalMarking; 
	};

	for (size_t i = 0; i < sizeOfSmallerGenome && IsHistoricalMarkingSameAt(i); ++i) {
		totalWeightDifference += (double)std::abs(const_cast<Genome&>(leftGenome)[i].weight - const_cast<Genome&>(rightGenome)[i].weight);
		++numberOfOverlapingGenes;
	}

	auto numberOfDisjointGenes = leftGenome.GetGeneCount() + rightGenome.GetGeneCount() - (size_t)2 * numberOfOverlapingGenes;
	auto sizeOfBiggerGenome = std::max(leftGenome.GetGeneCount(), rightGenome.GetGeneCount());
	auto disjointGenesInfluence = (double)numberOfDisjointGenes / (double)sizeOfBiggerGenome;

	auto averageWeightDifference = totalWeightDifference / (double)numberOfOverlapingGenes;

	disjointGenesInfluence *= (double)parameters.advanced.speciation.importanceOfDisjointGenes;
	averageWeightDifference *= (double)parameters.advanced.speciation.importanceOfAverageWeightDifference;

	return disjointGenesInfluence + averageWeightDifference;
}

void Species::ElectRepresentative()
{
	auto randomMember = rand() % population.size();
	representative = *population[randomMember];
}

template <class T>
constexpr bool Species::IsAboveCompatibilityThreshold(T t) const
{
	return t > parameters.advanced.speciation.compatibilityThreshold;
}
