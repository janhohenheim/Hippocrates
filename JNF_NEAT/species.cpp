#include "species.h"
#include <algorithm>
#include <cstdlib>

using namespace JNF_NEAT;
using namespace std;

Species::Species(Organism representative) :
parameters(representative.GetTrainingParameters()) {
	population.push_back(make_unique<Organism>(move(representative)));
	ElectRepresentative();
}

void Species::AddOrganism(Organism&& organism) {
	population.push_back(make_unique<Organism>(move(organism)));
	ElectRepresentative();
	isSortedByFitness = false;
	SetPopulationsFitnessModifier();
}

void Species::AnalyzeAndClearPopulation() {
	const auto currentBestFitness = GetFittestOrganism().GetOrCalculateRawFitness();
	if (currentBestFitness > fitnessHighscore) {
		fitnessHighscore = currentBestFitness;
		numberOfStagnantGenerations = 0;
	} else {
		numberOfStagnantGenerations++;
	}
	population.clear(); 
	isSortedByFitness = false;	
}


bool Species::IsCompatible(const Genome& genome) const {
	auto distanceToSpecies = representative->GetGenome().GetGeneticalDistanceFrom(genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

void Species::SetPopulationsFitnessModifier() {
	double fitnessModifier = 1.0 / (double)population.size();
	for (auto& organism : population){
		organism->SetFitnessModifier(fitnessModifier);
	}
}

void Species::ElectRepresentative() {
	if (!population.empty()) {
		SelectRandomRepresentative();
		//SelectFittestOrganismAsRepresentative();
	}
}

void Species::SelectRandomRepresentative() {
	auto randomMember = rand() % population.size();
	if (representative == nullptr) {
		representative = make_unique<Organism>(*population[randomMember]);
	} else {
		*representative = *population[randomMember];
	}
}

void Species::SelectFittestOrganismAsRepresentative() {
	if (representative == nullptr) {
		representative = make_unique<Organism>(GetFittestOrganism());
	} else {
		*representative = GetFittestOrganism();
	}
}

void Species::LetPopulationLive() {
	for (auto& organism : population){
		organism->Update();
	}
	isSortedByFitness = false;
}

void Species::ResetToTeachableState() {
	for (auto& organism : population){
		organism->Reset();
	}
}

Organism& Species::GetFittestOrganism() {
	if (population.empty()) {
		return *representative;
	}
	if (!isSortedByFitness) {
		auto CompareOrganisms = [&](unique_ptr<Organism>& lhs, unique_ptr<Organism>& rhs) {
			return lhs->GetOrCalculateFitness() > rhs->GetOrCalculateFitness();
		};
		sort(population.begin(), population.end(), CompareOrganisms);
		isSortedByFitness = true;
	}
	return *population.front();
}

Species& Species::operator=(Species&& other) {
	population = move(other.population);
	representative = move(other.representative);
	isSortedByFitness = move(other.isSortedByFitness);
	numberOfStagnantGenerations = move(other.numberOfStagnantGenerations);
	fitnessHighscore = move(other.fitnessHighscore);
	return *this;
}

Organism& Species::GetOrganismToBreed() {
	// TODO jnf: Switch to stochastic universal sampling
	if (population.empty()) {
		return *representative;
	}
	double totalPopulationFitness = 0.0;
	for (auto& organism : population) {
		totalPopulationFitness += organism->GetOrCalculateFitness();
	}
	if (totalPopulationFitness == 0) {
		return *population[rand() % population.size()];
	}
	double chance = 0.0;
	auto GetChanceForOrganism = [&chance, &totalPopulationFitness](Organism& organism) {
		return chance + (organism.GetOrCalculateFitness() / totalPopulationFitness);
	};

	while (true) {
		for (auto& organism : population) {
			double randNum = (double)(rand() % 10'000) / 9'999.0;;
			chance = GetChanceForOrganism(*organism);
			if (randNum < chance) {
				return *organism;
			}
		}
	}
}

string Species::GetJSON() const {
	string s("{\"fitnessHighscore\":");
	s += to_string(fitnessHighscore);
	s += ",\"numberOfStagnantGenerations\":";
	s += to_string(numberOfStagnantGenerations);
	s += ",\"representative\":";
	s += representative->GetJSON();
	s += ",\"population\": [";
	for (size_t i = 0; i < population.size() - 1; ++i) {
		s += population[i]->GetJSON();
		s += ",";
	}
	s += population.back()->GetJSON();
	s += "]}";
	return s;
}

