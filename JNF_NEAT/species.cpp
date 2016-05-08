#include "species.h"
#include <algorithm>

Species::Species(const Species & other) :
    population(other.population)
{
    ElectRepresentative();
}

Species::Species(Species && other) :
    population(std::move(other.population))
{
    ElectRepresentative();
}

Species::~Species()
{
    delete representative;
    representative = nullptr;
}

void Species::AddIndividual(const Genome& individual)
{
	population.push_back(individual);
	ElectRepresentative();
}

bool Species::IsCompatible(const Genome& genome) const {
	auto distanceToSpecies = representative->GetGeneticalDistanceFrom(genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

float Species::GetFitnessSharingModifier() const {
	unsigned int fitnessSharingDivisor = 1U;

	for (auto& lhs : population) {
		for (auto& rhs : population) {
			auto distance = lhs.get().GetGeneticalDistanceFrom(rhs);
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
        delete representative;
        representative = nullptr;
    } else {
        SelectRandomRepresentative();
    }
}

void Species::SelectRandomRepresentative() {
    auto randomMember = rand() % population.size();
    if (representative == nullptr) {
        representative = new Genome(population[randomMember]);
    }
    *representative = population[randomMember];
}

template <class T>
constexpr bool Species::IsAboveCompatibilityThreshold(T t) const
{
	return t > representative->GetTrainingParameters().advanced.speciation.compatibilityThreshold;
}
