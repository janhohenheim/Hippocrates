#include "species.h"
#include <algorithm>

Species::Species(const TrainingParameters& parameters) :
	parameters(parameters)
{
}

Species::Species(const Species & other) :
    parameters(other.parameters),
    population(other.population)
{
    ElectRepresentative();
}

Species::Species(Species && other) :
    parameters(std::move(other.parameters)),
    population(std::move(other.population))
{
    ElectRepresentative();
}

Species::~Species()
{
    DeleteRepresentative();
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
	auto distanceToSpecies = representative->GetGenome().GetGeneticalDistanceFrom(genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

float Species::GetFitnessSharingModifier() const {
	unsigned int fitnessSharingDivisor = 1U;

	for (auto& lhs : population) {
		for (auto& rhs : population) {
			auto distance = lhs->GetGenome().GetGeneticalDistanceFrom(rhs->GetGenome());
			if (IsAboveCompatibilityThreshold(distance)) {
				++fitnessSharingDivisor;
			}
		}
	}

	float fitnessSharingFactor = 1.0f / (float)fitnessSharingDivisor;
	return fitnessSharingFactor;
}



void Species::ElectRepresentative()
{
    if (population.empty()) {
        DeleteRepresentative();
    } else {
        SelectRandomRepresentative();
    }
}

void Species::DeleteRepresentative() {
    if (representative != nullptr) {
        delete representative;
        representative = nullptr;
    }
}

void Species::SelectRandomRepresentative() {
    auto randomMember = rand() % population.size();
    if (representative == nullptr) {
        representative = new NeuralNetwork(*population[randomMember]);
    }
    *representative = *population[randomMember];
}

template <class T>
constexpr bool Species::IsAboveCompatibilityThreshold(T t) const
{
	return t > parameters.advanced.speciation.compatibilityThreshold;
}
