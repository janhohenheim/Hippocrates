#include "gene.h"
#include <stdlib.h>

size_t Gene::numberOfExistingGenes = 0U;

Gene::Gene() {
	SetRandomWeight();
	numberOfExistingGenes++;
}

void Gene::SetRandomWeight() {
    /*
    const auto& min = parameters.advanced.ranges.minWeight;
    const auto& max = parameters.advanced.ranges.maxWeight;
    if (min == max) {
    weight = min;
    }
    else {
    weight = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    }
    */
	weight = (float)(rand() % 10'000) / 9'999.0f;
	if (rand() % 2) {
		weight = -weight;
	}
}