#pragma once
#include "neuron.h"
class Gene
{
	public:
		Gene(Neuron & from, Neuron & to);
		Gene(const Gene & other) = default;
		
		unsigned int GetHistoricalMarking() const;

	private:
		Neuron & fromNeuron;
		Neuron & toNeuron;
		static unsigned int numberOfExistingGenes;
		unsigned int historicalMarking = numberOfExistingGenes;
		bool isEnabled = true;
};
