#include "gene.h"

unsigned int Gene::numberOfExistingGenes = 0;

Gene::Gene(Neuron & from, Neuron & to):
	fromNeuron(from),
	toNeuron(to)
{
	numberOfExistingGenes++;
}

unsigned int Gene::GetHistoricalMarking() const
{
	return historicalMarking;
}
