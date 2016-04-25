#include "species.h"
#include <algorithm>

Species::Species(const TrainingParameters & parameters) :
	parameters(parameters),
	representative(parameters.numberOfInputs, parameters.numberOfOutputs)
{
}

void Species::AddIndividual(NeuralNetwork & individual)
{
	population.push_back(&individual);
	ElectRepresentative();
}

void Species::SetPopulation(std::vector<NeuralNetwork> & population)
{
	this->population.empty();
	this->population.reserve(population.size());
	for (auto & individual : population) {
		this->population.push_back(&individual);
	}
	ElectRepresentative();
}

bool Species::IsCompatible(const NeuralNetwork & network) const {
	return IsCompatible(network.GetGenes());
}

bool Species::IsCompatible(const std::vector<Gene> & genome) const {
	auto distanceToSpecies = GetGeneticalDistance(representative.GetGenes(), genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

float Species::GetFitnessSharingModifier() const{
	unsigned int fitnessSharingDivisor = 0;

	for (auto & lhs : population) {
		for (auto & rhs : population) {
			auto distance = GetGeneticalDistance(lhs->GetGenes(), rhs->GetGenes());
			if (IsAboveCompatibilityThreshold(distance)) {
				++fitnessSharingDivisor;
			}
		}
	}

	float fitnessSharingFactor = 1.0f / (float) fitnessSharingDivisor;
	return fitnessSharingFactor;
}

double Species::GetGeneticalDistance(const std::vector<Gene> & leftGenome, const std::vector<Gene> & rightGenome) const
{
	double totalWeightDifference = 0.0;
	size_t numberOfOverlapingGenes = 0;

	size_t sizeOfSmallerGenome = std::min(leftGenome.size(), rightGenome.size());
	for (size_t i = 0; i < sizeOfSmallerGenome && leftGenome[i].historicalMarking == rightGenome[i].historicalMarking; ++i) {
		totalWeightDifference += (double)std::abs(leftGenome[i].weight - rightGenome[i].weight);
		++numberOfOverlapingGenes;
	}

	auto numberOfDisjointGenes = leftGenome.size() + rightGenome.size() - (size_t)2 * numberOfOverlapingGenes;
	auto sizeOfBiggerGenome = std::max(leftGenome.size(), rightGenome.size());
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
