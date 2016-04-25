#include "individual.h"

Individual::Individual(ITrainable * trainable, const TrainingParameters & parameters) :
	trainable(trainable),
	network(parameters.numberOfInputs, parameters.numberOfOutputs)
{
}

Individual::Individual(ITrainable * trainable, NeuralNetwork network) :
	trainable(trainable),
	network(network)
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

void Individual::CoupleWithSpecies(Species & species)
{
	species.AddIndividual(network);
	this->species = &species;
}