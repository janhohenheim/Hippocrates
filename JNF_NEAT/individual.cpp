#include "individual.h"

Individual::Individual(ITrainable* trainable, const TrainingParameters& parameters) :
	trainable(trainable),
	parameters(parameters),
	network(parameters)
{
}

Individual::Individual(ITrainable* trainable, const TrainingParameters& parameters, NeuralNetwork&& network) :
	trainable(trainable),
	parameters(parameters),
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
		fitness = (int)((float)trainable->GetOrCalculateFitness() * species->GetFitnessSharingModifier());
		isFitnessUpToDate = true;
	}
	return fitness;
}

void Individual::CoupleWithSpecies(Species& species)
{
	species.AddIndividual(network);
	this->species = &species;
}

Individual Individual::BreedWith(Individual* partner) const
{
	Individual* dominantParent = nullptr;
	Genome childGenome(this->network.GetGenome());

	if (trainable->GetOrCalculateFitness() == partner->GetOrCalculateFitness()) {
		// TODO jnf
		// Do Stuff with the genes
	} else {
		// TODO jnf
		// Do Stuff with the genes
	}
	childGenome.MutateGenes();

	Individual child(dominantParent->trainable, parameters, std::move(NeuralNetwork(parameters, childGenome)));
	// It may look ineffective to return this by value, accessing the copy constructor
	// But don't worry, RVO will take care of this.
	// If your compiler doesn't optimize this, I'd recommend using what you'd call an "out parameter" in C#
	return child;
}
