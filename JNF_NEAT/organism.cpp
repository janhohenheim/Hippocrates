#include <cstdlib>
#include <algorithm>
#include "organism.h"

using namespace JNF_NEAT;
using namespace std;

Organism::Organism(std::shared_ptr<IBody> body, NeuralNetwork&& network) :
	body(body),
	network(move(network))
{
}

void Organism::Update() {
	const auto inputs( move(body->ProvideNetworkWithInputs()) );
	const auto outputs( move(network.GetOutputsUsingInputs(inputs)) );
	body->Update(outputs);
	isFitnessUpToDate = false;
}

double Organism::GetOrCalculateFitness() {
	return GetOrCalculateRawFitness() * fitnessModifier;
}

double Organism::GetOrCalculateRawFitness() {
	if (!isFitnessUpToDate) {
		fitness = body->GetFitness();
		isFitnessUpToDate = true;
	}
	return fitness;
}

NeuralNetwork Organism::BreedWith(Organism& partner) {
	bool parentsHaveSameFitness = this->GetOrCalculateFitness() == partner.GetOrCalculateFitness();
	Organism* dominantParent = nullptr;
	if (parentsHaveSameFitness) {
		dominantParent = rand() % 2 == 0 ? this : &partner;
	}
	else {
		dominantParent = this->GetOrCalculateFitness() > partner.GetOrCalculateFitness() ? this : &partner;
	}
	Genome childGenome(dominantParent->GetGenome());

	size_t sizeOfSmallerParent = min(this->GetGenome().GetGeneCount(), partner.GetGenome().GetGeneCount());
	auto & partnerGenome = partner.GetGenome();
	auto AreMarkingsSameAt = [&](size_t i) {
		return childGenome[i].historicalMarking == partnerGenome[i].historicalMarking;
	};
	for (size_t i = 0U;	i < sizeOfSmallerParent && AreMarkingsSameAt(i); ++i) {
		if (rand() % 2 == 0) {
			childGenome[i].weight = partnerGenome[i].weight;
		}
	}
	NeuralNetwork child(move(childGenome), true);
	// It may look ineffective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return child;
}

string Organism::GetJSON() const {
	string s("{\"fitness\":");
	s += to_string(fitness);
	s += ",";
	s += "\"fitnessModifier\":"; 
	s += to_string(fitnessModifier);
	s += ",";
	s += "\"network\":";
	s += network.GetJSON();
	s += "}";
	return s;
}