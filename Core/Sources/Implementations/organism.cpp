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
	const auto inputs(move(body->ProvideNetworkWithInputs()));
	const auto outputs(move(network.GetOutputsUsingInputs(inputs)));
	body->Update(outputs);
	isFitnessUpToDate = false;
}

auto Organism::GetOrCalculateFitness() const -> double {
	return GetOrCalculateRawFitness() * fitnessModifier;
}

auto Organism::GetOrCalculateRawFitness() const -> double {
	if (!isFitnessUpToDate) {
		fitness = body->GetFitness();
		isFitnessUpToDate = true;
	}
	return fitness;
}

auto Organism::BreedWith(Organism& partner) -> NeuralNetwork {
	auto parentsHaveSameFitness = this->GetOrCalculateFitness() == partner.GetOrCalculateFitness();
	Organism* dominantParent = nullptr;
	if (parentsHaveSameFitness) {
		dominantParent = Utility::FlipACoin() ? this : &partner;
	}
	else {
		dominantParent = this->GetOrCalculateFitness() > partner.GetOrCalculateFitness() ? this : &partner;
	}
	auto childGenome(dominantParent->GetGenome());

	const auto sizeOfSmallerParent = min(this->GetGenome().GetGeneCount(), partner.GetGenome().GetGeneCount());
	auto& partnerGenome = partner.GetGenome();
	auto AreMarkingsSameAt = [&](size_t i) {
		return childGenome[i].historicalMarking == partnerGenome[i].historicalMarking;
	};
	for (size_t i = 0U; i < sizeOfSmallerParent && AreMarkingsSameAt(i); ++i) {
		if (Utility::FlipACoin()) {
			childGenome[i].weight = partnerGenome[i].weight;
		}
	}
	NeuralNetwork child(move(childGenome), true);
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

