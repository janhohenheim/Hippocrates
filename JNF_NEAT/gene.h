#pragma once
#include "neuron.h"

struct Gene {
	public:
		Gene();
		~Gene() = default;
		Gene(const Gene & other) = default;
        Gene(Gene && other) = default;
		Gene & operator=(const Gene & other) = default;

        size_t from = 0;
		size_t to = 0;
		float weight = 0.0f;
        size_t historicalMarking = numberOfExistingGenes;
		bool isEnabled = true;
		void SetRandomWeight();
	private:
		static size_t numberOfExistingGenes;
};