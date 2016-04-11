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
		unsigned int layer = 0U;
		float weight = 0.0f;
		const unsigned int historicalMarking = numberOfExistingGenes;
		bool isEnabled = false;
		void SetRandomWeight();
	private:
		static unsigned int numberOfExistingGenes;
};