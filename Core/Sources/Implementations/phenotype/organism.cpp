#include <cstdlib>
#include <algorithm>
#include "../Headers/organism.hpp"

using namespace Hippocrates;
using namespace std;

Organism::Organism(IBody& body, NeuralNetwork&& network) :
	body(&body),
	network(move(network))
{
}

auto Organism::Update() -> void {
	size_t numberOfTimesToFinishTask = 1;

	if (GetParameters().structure.allowRecurrentConnections) {
		numberOfTimesToFinishTask = GetParameters().structure.memoryResetsBeforeTotalReset;
	}

	for (size_t i = 0; i < numberOfTimesToFinishTask; i++) {
		while (!body->HasFinishedTask()) {
			const auto inputs(move(body->ProvideNetworkWithInputs()));
			const auto outputs(move(network.GetOutputsUsingInputs(inputs)));
			body->Update(outputs);
			isFitnessUpToDate = false;
		}
	}
}

auto Organism::GetOrCalculateFitness() const -> Type::fitness_t {
	return GetOrCalculateRawFitness() * fitnessModifier;
}

auto Organism::GetOrCalculateRawFitness() const -> Type::fitness_t {
	if (!isFitnessUpToDate) {
		fitness = body->GetFitness();
		isFitnessUpToDate = true;
	}
	return fitness;
}

auto Organism::BreedWith(const Organism& partner, InnovationCacher& currGenerationInnovations) const -> NeuralNetwork {
	auto parentsHaveSameFitness = this->GetOrCalculateFitness() == partner.GetOrCalculateFitness();
	const Organism* dominantParent = nullptr;
	if (parentsHaveSameFitness) {
		dominantParent = Utility::FlipACoin() ? this : &partner;
	}
	else {
		dominantParent = this->GetOrCalculateFitness() > partner.GetOrCalculateFitness() ? this : &partner;
	}
	// TODO jnf: conform to the paper
	auto childGenome(dominantParent->GetGenome());

	const auto sizeOfSmallerParent = min(this->GetGenome().GetGeneCount(), partner.GetGenome().GetGeneCount());
	auto& partnerGenome = partner.GetGenome();
	auto AreSameAt = [&](size_t i) {
		return childGenome[i] == partnerGenome[i];
	};
	for (size_t i = 0U; i < sizeOfSmallerParent && AreSameAt(i); ++i) {
		if (Utility::FlipACoin()) {
			childGenome[i].weight = partnerGenome[i].weight;
		}
	}
	NeuralNetwork child(move(childGenome), currGenerationInnovations);
	return child;
}

auto Organism::GetJSON() const -> string {
	string s("{\"fitness\":");
	s += to_string(GetOrCalculateRawFitness());
	s += ",";
	s += "\"fitnessModifier\":";
	s += to_string(fitnessModifier);
	s += ",";
	s += "\"network\":";
	s += network.GetJSON();
	s += "}";
	return s;
}

