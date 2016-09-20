#include <algorithm>
#include "../Headers/species.h"

using namespace JNF_NEAT;
using namespace std;

Species::Species(Organism representative):
parameters(representative.GetTrainingParameters()),
representative(representative)
{
	population.push_back(move(representative));
}

auto Species::AddOrganism(Organism&& organism) -> void {
	population.push_back(move(organism));
	ElectRepresentative();
	isSortedByFitness = false;
	SetPopulationsFitnessModifier();
}

auto Species::AnalyzePopulation() -> void {
	const auto currentBestFitness = GetFittestOrganism().GetOrCalculateRawFitness();
	if (currentBestFitness > fitnessHighscore) {
		fitnessHighscore = currentBestFitness;
		numberOfStagnantGenerations = 0;
	}
	else {
		numberOfStagnantGenerations++;
	}
	isSortedByFitness = false;
}


auto Species::IsCompatible(const Genome& genome) const -> bool {
	auto distanceToSpecies = representative.GetGenome().GetGeneticalDistanceFrom(genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

auto Species::SetPopulationsFitnessModifier() -> void {
	double fitnessModifier = 1.0 / static_cast<double>(population.size());
	for (auto& organism : population) {
		organism.SetFitnessModifier(fitnessModifier);
	}
}

auto Species::ClearPopulation() -> void {
	population.clear();
}

auto Species::ElectRepresentative() -> void {
	if (!population.empty()) {
		SelectRandomRepresentative();
		//SelectFittestOrganismAsRepresentative();
	}
}

auto Species::SelectRandomRepresentative() -> void {
	auto randomMember = rand() % population.size();
	representative = population[randomMember];
}

auto Species::SelectFittestOrganismAsRepresentative() -> void {
	representative = GetFittestOrganism();
}

auto JNF_NEAT::Species::IsStagnant() const -> bool {
	return numberOfStagnantGenerations >= 
		parameters.		
		speciation.
		stagnantSpeciesClearThreshold;
}

auto Species::LetPopulationLive() -> void {
	for (auto& organism : population) {
		while (!organism.HasFinishedTask()) {
			organism.Update();
		}
	}
	isSortedByFitness = false;
}

auto Species::ResetToTeachableState() -> void {
	for (auto& organism : population) {
		organism.Reset();
	}
}

auto Species::GetFittestOrganism() const -> const Organism& {
	if (population.empty()) {
		return representative;
	}
	SortPopulationIfNeeded();
	return population.front();
}

auto Species::SortPopulationIfNeeded() const -> void {
	if (!isSortedByFitness) {
		auto CompareOrganisms = [](const auto& lhs, const auto& rhs) {
			return lhs.GetOrCalculateFitness() > rhs.GetOrCalculateFitness();
		};
		sort(population.begin(), population.end(), CompareOrganisms);
		isSortedByFitness = true;
	}
}

auto Species::operator=(Species&& other) noexcept -> Species& {
	population = move(other.population);
	representative = move(other.representative);
	isSortedByFitness = move(other.isSortedByFitness);
	numberOfStagnantGenerations = move(other.numberOfStagnantGenerations);
	fitnessHighscore = move(other.fitnessHighscore);
	return *this;
}

auto Species::GetOrganismToBreed() -> Organism& {
	// TODO jnf: Switch to stochastic universal sampling
	if (population.empty()) {
		return representative;
	}
	double totalPopulationFitness = 0.0;
	for (auto& organism : population) {
		totalPopulationFitness += organism.GetOrCalculateFitness();
	}
	if (totalPopulationFitness == 0) {
		return population[rand() % population.size()];
	}
	double chance = 0.0;
	auto GetChanceForOrganism = [&chance, &totalPopulationFitness](const Organism& organism) {
		return chance + (organism.GetOrCalculateFitness() / totalPopulationFitness);
	};

	while (true) {
		for (auto& organism : population) {
			double randNum = static_cast<double>(rand() % 10'000) / 9'999.0;;
			chance = GetChanceForOrganism(organism);
			if (randNum < chance) {
				return organism;
			}
		}
	}
}

auto Species::GetJSON() const -> string {
	string s("{\"fitnessHighscore\":");
	s += to_string(fitnessHighscore);
	s += ",\"numberOfStagnantGenerations\":";
	s += to_string(numberOfStagnantGenerations);
	s += ",\"representative\":";
	s += representative.GetJSON();
	s += ",\"population\": [";
	for (const auto& sp : population) {
		s += sp.GetJSON();
		s += ",";
	}
	s.pop_back();
	s += "]}";
	return s;
}

