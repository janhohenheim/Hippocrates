#include <algorithm>
#include "../Headers/species.hpp"

using namespace Hippocrates;
using namespace std;

Species::Species(Organism representative):
representative(representative)
{
	population.push_back(move(representative));
}

auto Species::AddOrganism(Organism&& organism) -> void {
	population.push_back(move(organism));
	isSortedByFitness = false;
	SetPopulationsFitnessModifier();
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
	const auto currentBestFitness = GetFittestOrganism().GetOrCalculateRawFitness();
	if (currentBestFitness > fitnessHighscore) {
		fitnessHighscore = currentBestFitness;
		numberOfStagnantGenerations = 0;
	} else {
		numberOfStagnantGenerations++;
	}

	ElectRepresentative();
	population.clear();
}

auto Hippocrates::Species::RemoveWorst() -> void {
	if (GetSize() > 1)
		population.pop_back();
}

auto Species::ElectRepresentative() -> void {
	if (!population.empty()) {
		SelectRandomRepresentative();
		//SelectFittestOrganismAsRepresentative();
	}
}

auto Species::SelectRandomRepresentative() -> void {
	representative = *Utility::GetRandomElement(population);
}

auto Species::SelectFittestOrganismAsRepresentative() -> void {
	representative = GetFittestOrganism();
}

auto Hippocrates::Species::IsStagnant() const -> bool {
	return numberOfStagnantGenerations >=
		GetTrainingParameters().
		speciation.
		stagnantSpeciesClearThreshold;
}

auto Species::GetOffspringCount(double averageFitness) const -> std::size_t {
	if (IsStagnant())
		return 0;

	if (averageFitness == 0.0) 
		return GetSize();
	

	std::size_t offspringCount = 0;
	for (auto & organism : population) {
		// TODO jnf: Should we round this?
		offspringCount += static_cast<std::size_t>(std::round(organism.GetOrCalculateFitness() / averageFitness));
	}
	return offspringCount;
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


auto Species::GetOrganismToBreed() const -> const Organism& {
	// TODO jnf: Switch to stochastic universal sampling
	double totalPopulationFitness = 0.0;
	for (auto& organism : population) {
		totalPopulationFitness += organism.GetOrCalculateFitness();
	}
	if (totalPopulationFitness == 0) {
		return *Utility::GetRandomElement(population);
	}
	double chance = 0.0;
	auto GetChanceForOrganism = [&chance, &totalPopulationFitness](const Organism& organism) {
		return chance + (organism.GetOrCalculateFitness() / totalPopulationFitness);
	};

	while (true) {
		for (auto& organism : population) {
			chance = GetChanceForOrganism(organism);
			if (Utility::DidChanceOccure(chance))
				return organism;
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

auto Species::GetAverageFitness() const -> double {
	return GetTotalFitness() / GetSize();
}

auto Species::GetTotalFitness() const -> double {
	auto totalFitness = 0.0;
	for (auto & organism : population) {
		totalFitness += organism.GetOrCalculateFitness();
	}
	return totalFitness;
}
