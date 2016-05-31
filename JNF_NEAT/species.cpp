#include "species.h"
#include <algorithm>

Species::Species(const Organism& representative) {
	population.push_back(new Organism(representative));
	ElectRepresentative();
}

Species::Species(Organism && representative) {
	population.push_back(new Organism(std::move(representative)));
	ElectRepresentative();
}

Species::Species(const Species & other) :
	population(other.population)
{
	representative = new Genome(*other.representative);
}

Species::Species(Species && other) :
	population(std::move(other.population))
{
	representative = new Genome(std::move(*other.representative));
}

Species::~Species() {
	delete representative;
	representative = nullptr;
    for (auto* organism : population) {
        delete organism;
        organism = nullptr;
    }
}

void Species::AddOrganism(const Organism &organism) {
	population.push_back(new Organism(organism));
	ElectRepresentative();
	isSortedByFitness = false;
}

void Species::AddOrganism(Organism &&organism) {
	population.push_back(new Organism(std::move(organism)));
	ElectRepresentative();
	isSortedByFitness = false;
}

void Species::Clear()
{
    for (auto* organism : population) {
        delete organism;
        organism = nullptr;
    }
    population.clear(); 
    isSortedByFitness = false;
}


bool Species::IsCompatible(const Genome& genome) const {
	auto distanceToSpecies = representative->GetGeneticalDistanceFrom(genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

void Species::SetPopulationsFitnessModifier() {
	float fitnessModifier = 1.0f / (float)population.size();
	for (auto* organism : population){
		organism->SetFitnessModifier(fitnessModifier);
	}
}

void Species::ElectRepresentative() {
	if (population.empty()) {
		delete representative;
		representative = nullptr;
	}
	else {
		SelectRandomRepresentative();
	}
}

void Species::SelectRandomRepresentative() {
	auto randomMember = rand() % population.size();
	if (representative == nullptr) {
		representative = new Genome(population[randomMember]->GetGenome());
    }
    else {
        *representative = population[randomMember]->GetGenome();
    }
}

template <class T>
constexpr bool Species::IsAboveCompatibilityThreshold(T t) const
{
	return t > representative->GetTrainingParameters().advanced.speciation.compatibilityThreshold;
}

void Species::LetPopulationLive() {
	for (auto* organism : population){
		organism->Update();
	}
}

void Species::ResetToTeachableState() {
	for (auto* organism : population){
		organism->Reset();
	}
}

Organism& Species::GetFittestOrganism() {
	if (!isSortedByFitness) {
		auto CompareOrganisms = [&](Organism* lhs, Organism* rhs) {
			return lhs->GetOrCalculateFitness() < rhs->GetOrCalculateFitness();
		};
		std::sort(population.begin(), population.end(), CompareOrganisms);
		isSortedByFitness = true;
	}
	return *population.front();
}

Species& Species::operator=(Species &&other) {
	population = std::move(other.population);
	ElectRepresentative();
	return *this;
}

Organism& Species::GetOrganismToBreed() {
	// TODO jnf: Switch to stochastic universal sampling
	auto totalSpeciesFitness = 0;
	for (auto* organism : population) {
		totalSpeciesFitness += organism->GetOrCalculateFitness();
	}
	double chance = 0.0;
	auto GetChanceForOrganism = [&chance, &totalSpeciesFitness](Organism& organism) {
		return chance + ((double)organism.GetOrCalculateFitness() / (double)totalSpeciesFitness);
	};
	for (auto* organism : population) {
		double randNum = (double)(rand() % 10'000) / 9'999.0;;
		chance = GetChanceForOrganism(*organism);
		if (randNum < chance) {
			return *organism;
		}
	}
	return *population.front();
}