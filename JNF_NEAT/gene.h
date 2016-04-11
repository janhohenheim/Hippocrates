#pragma once
#include "neuron.h"

struct Gene {
	public:
		Gene();
		~Gene() = default;
		Gene(const Gene & other) = default;
        Gene(Gene && other) = default;

		unsigned int from = 0U;
		unsigned int to = 0U;
		float weight = 0.0f;
		const unsigned int historicalMarking = numberOfExistingGenes;
		bool isEnabled = true;
		void SetRandomWeight();
	private:
		static unsigned int numberOfExistingGenes;
};