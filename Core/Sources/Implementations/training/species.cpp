#include <algorithm>
#include <string>

#include "training/species.hpp"
#include "utility/random.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Training;

Species::Species(Phenotype::Organism representative):
representative(representative)
{
	population.push_back(std::move(representative));
}

auto Species::AddOrganism(Phenotype::Organism&& organism) -> void {
	population.push_back(std::move(organism));
	isSortedByFitness = false;
	SetPopulationsFitnessModifier();
}

auto Species::IsCompatible(const Genotype::Genome& genome) const -> bool {
	auto distanceToSpecies = representative.GetGenome().GetGeneticalDistanceFrom(genome);
	return !IsAboveCompatibilityThreshold(distanceToSpecies);
}

auto Species::SetPopulationsFitnessModifier() -> void {
	auto fitnessModifier = static_cast<Type::fitness_t>(1.0) / static_cast<Type::fitness_t>(population.size());
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

auto Species::RemoveWorst() -> void {
	const auto threshold = GetParameters().reproduction.reproductionThreshold;
	const auto size = static_cast<double>(GetSize());
	const auto numberOfPotentionalParents = static_cast<std::size_t>(size * threshold);

	const auto minParents = GetParameters().reproduction.minParents;
	const auto lastParent = population.begin() + std::max(numberOfPotentionalParents, minParents);

	population.erase(lastParent, population.end());
}

auto Species::ElectRepresentative() -> void {
	if (!population.empty()) {
		SelectRandomRepresentative();
		//SelectFittestOrganismAsRepresentative();
	}
}

auto Species::SelectRandomRepresentative() -> void {
	representative = *Utility::Random::Element(population);
}

auto Species::SelectFittestOrganismAsRepresentative() -> void {
	representative = GetFittestOrganism();
}

auto Species::IsStagnant() const -> bool {
	return numberOfStagnantGenerations >=
		GetParameters().
		speciation.
		stagnantSpeciesClearThreshold;
}

auto Species::GetOffspringCount(Type::fitness_t averageFitness) const -> std::size_t {
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
		organism.Update();
	}

	isSortedByFitness = false;
}

auto Species::ResetToTeachableState() -> void {
	for (auto& organism : population) {
		organism.Reset();
	}
}

auto Species::GetFittestOrganism() const -> const Phenotype::Organism& {
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


auto Species::GetOrganismToBreed() const -> const Phenotype::Organism& {
	// TODO jnf: Switch to stochastic universal sampling
	Type::fitness_t totalPopulationFitness = 0.0;
	for (auto& organism : population) {
		totalPopulationFitness += organism.GetOrCalculateFitness();
	}
	if (totalPopulationFitness == 0) {
		return *Utility::Random::Element(population);
	}
	double chance = 0.0;
	auto GetChanceForOrganism = [&chance, &totalPopulationFitness](const Phenotype::Organism& organism) {
		return chance + (organism.GetOrCalculateFitness() / totalPopulationFitness);
	};

	while (true) {
		for (auto& organism : population) {
			chance = GetChanceForOrganism(organism);
			if (Utility::Random::DidChanceOccure(chance))
				return organism;
		}
	}
}

auto Species::GetJSON() const -> std::string {
	std::string s("{\"fitnessHighscore\":");
	s += std::to_string(fitnessHighscore);
	s += ",\"numberOfStagnantGenerations\":";
	s += std::to_string(numberOfStagnantGenerations);
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

auto Species::GetAverageFitness() const -> Type::fitness_t {
	return GetTotalFitness() / GetSize();
}

auto Species::GetTotalFitness() const -> Type::fitness_t {
	auto totalFitness = 0.0;
	for (auto & organism : population) {
		totalFitness += organism.GetOrCalculateFitness();
	}
	return totalFitness;
}
