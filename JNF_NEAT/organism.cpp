#include <cstdlib>
#include <algorithm>
#include "organism.h"

Organism::Organism(IBody* trainer, NeuralNetwork&& network) :
	trainer(trainer),
	network(std::move(network))
{
}

void Organism::Update()
{
	network.SetInputs(trainer->ProvideNetworkWithInputs());
	trainer->Update(network.GetOutputs());
	isFitnessUpToDate = false;
}


int Organism::GetOrCalculateFitness()
{
	if (!isFitnessUpToDate) {
		fitness = trainer->GetFitness();
		isFitnessUpToDate = true;
	}
	return (int)((float)fitness * fitnessModifier);
}

NeuralNetwork Organism::BreedWith(Organism& partner)
{
	bool parentsHaveSameFitness = this->GetOrCalculateFitness() == partner.GetOrCalculateFitness();
	Organism* dominantParent = nullptr;
	if (parentsHaveSameFitness) {
		dominantParent = rand() % 2 == 0 ? this : &partner;
	}
	else {
		dominantParent = this->GetOrCalculateFitness() > partner.GetOrCalculateFitness() ? this : &partner;
	}
	Genome childGenome(dominantParent->GetGenome());

	size_t sizeOfSmallerParent = std::min(this->GetGenome().GetGeneCount(), partner.GetGenome().GetGeneCount());
	auto & partnerGenome = partner.GetGenome();
	auto AreMarkingsSameAt = [&](size_t i) {
		return childGenome[i].historicalMarking == partnerGenome[i].historicalMarking;
	};
	for (size_t i = 0U;	i < sizeOfSmallerParent && AreMarkingsSameAt(i); ++i) {
		if (rand() % 2 == 0) {
			// TODO jnf:
			// This can lead to a child with only disabled genes!
			childGenome[i] = partnerGenome[i];
		}
	}
	NeuralNetwork child(std::move(childGenome));
	// It may look ineffective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return child;
}
