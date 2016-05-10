#include <cstdlib>
#include "organism.h"

Organism::Organism(INetworkTrainer* trainer, NeuralNetwork&& network) :
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

Genome Organism::BreedWith(Organism& partner)
{
    bool parentsHaveSameFitness = this->GetOrCalculateFitness() == partner.GetOrCalculateFitness();
    Organism* dominantOrLargerParent = nullptr;
    auto & partnerGenome = partner.GetGenome();
    if (parentsHaveSameFitness) {
        // TODO jnf remove feature envy
        dominantOrLargerParent = this->GetGenome().GetGeneCount() > partnerGenome.GetGeneCount() ? this : &partner;
    }
    else {
        dominantOrLargerParent = this->GetOrCalculateFitness() > partner.GetOrCalculateFitness() ? this : &partner;
    }
	Genome childGenome(dominantOrLargerParent->GetGenome());

	size_t i = 0U;
    while (i < childGenome.GetGeneCount() && childGenome[i].historicalMarking == partnerGenome[i].historicalMarking) {
        if (rand() % 2 == 0) {
            childGenome[i] = partnerGenome[i];
        }
        ++i;
    }
	if (parentsHaveSameFitness) {
		// TODO jnf Remove double code
        while (i < dominantOrLargerParent->GetGenome().GetGeneCount()) {
            if (rand() % 2 == 0) {
                childGenome[i] = partnerGenome[i];
            }
            ++i;
        }
	} 
	childGenome.MutateGenes();
	// It may look ineffective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return childGenome;
}