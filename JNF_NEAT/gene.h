#pragma once
#include "neuron.h"

struct Gene {
	public:
		Gene();
		~Gene() = default;
		Gene(const Gene & other) = default;

		unsigned int from = 0;
		unsigned int to = 0;
		double weight = 0.0;
		const unsigned int historicalMarking = numberOfExistingGenes;
		bool isEnabled = false;

	private:
		static unsigned int numberOfExistingGenes;
};
