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

void Species::AddOrganism(const Organism &organism)
{
	population.push_back(organism);
	ElectRepresentative();
}

void Species::AddOrganism(Organism &&organism) {
	population.push_back(std::move(organism));
	ElectRepresentative();
}


bool Species::IsCompatible(const Genome& genome) const {
	auto distanceToSpecies = representative->GetGeneticalDistanceFrom(genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

void Species::SetPopulationsFitnessModifier() {
	unsigned int fitnessSharingDivisor = 1U;

	for (auto& lhs : population) {
		for (auto& rhs : population) {
			auto distance = lhs.GetGenome().GetGeneticalDistanceFrom(rhs.GetGenome());
			if (IsAboveCompatibilityThreshold(distance)) {
				++fitnessSharingDivisor;
			}
		}
	}

	float fitnessSharingFactor = 1.0f / (float)fitnessSharingDivisor;

	for (auto& organism : population){
		organism.SetFitnessModifier(fitnessSharingFactor);
	}
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
        representative = new Genome(population[randomMember].GetGenome());
    }
    *representative = population[randomMember].GetGenome();
}

template <class T>
constexpr bool Species::IsAboveCompatibilityThreshold(T t) const
{
	return t > representative->GetTrainingParameters().advanced.speciation.compatibilityThreshold;
}

void Species::LetPopulationLive() {
	for (auto& individal : population){
		individal.Update();
	}
}

void Species::ResetToTeachableState() {
	for (auto& individal : population){
		individal.Reset();
	}
}

Organism& Species::GetFittestOrganism() {
	// TODO jnf: Implementation with caching
	auto CompareOrganisms = [&](Organism& lhs, Organism& rhs) {
		return lhs.GetOrCalculateFitness() < rhs.GetOrCalculateFitness();
	};
	std::sort(population.begin(), population.end(), CompareOrganisms);
	return population.front();
}

Species &Species::operator=(Species &&other) {
	population = std::move(other.population);
	ElectRepresentative();
	return *this;
}









