#pragma once
#include "neuron.h"

struct Gene {
	public:
		Gene();
		~Gene() = default;
		Gene(const Gene & other) = delete;

		unsigned int from = 0U;
		unsigned int to = 0U;
		unsigned int layer = 0U;
		double weight = 0.0;
		const unsigned int historicalMarking = numberOfExistingGenes;
		bool isEnabled = false;

	private:
		static unsigned int numberOfExistingGenes;
};
