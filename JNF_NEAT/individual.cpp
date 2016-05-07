#include "individual.h"

Individual::Individual(ITrainable* trainable, NeuralNetwork&& network) :
	trainable(trainable),
	network(std::move(network))
{
}

void Individual::Update()
{
	network.SetInputs(trainable->ProvideNetworkWithInputs());
	trainable->Update(network.GetOutputs());
	isFitnessUpToDate = false;
}

void Individual::ModifyFitness(float factor)
{
	fitness = (int)((float)fitness * factor);
}

int Individual::GetOrCalculateFitness()
{
	if (!isFitnessUpToDate) {
		fitness = (int)((float)trainable->GetFitness() * species->GetFitnessSharingModifier());
		isFitnessUpToDate = true;
	}
	return fitness;
}

void Individual::CoupleWithSpecies(Species& species)
{
	species.AddIndividual(network.GetGenome());
	this->species = &species;
}

Genome Individual::BreedWith(Individual& partner)
{
    bool parentsHaveSameFitness = this->GetOrCalculateFitness() == partner.GetOrCalculateFitness();
    Individual* dominantOrLargerParent = nullptr;
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
