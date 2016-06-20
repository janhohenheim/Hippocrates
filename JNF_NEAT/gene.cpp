#include "gene.h"
#include <stdlib.h>

using namespace JNF_NEAT;
using namespace std;

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

std::string Gene::ToSTring() const {
	string s("Gene Data:\n");
	s+=		 "Historical marking: " + to_string(historicalMarking) + "\n"
			+ "from: " + to_string(from) + "\n"
			+ "to: " + to_string(to) + "\n"
			+ "weight: " + to_string(weight) + "\n"
			+ "is enabled: " + to_string(isEnabled) + "\n"
			+ "is recursive: " + to_string(isRecursive) + "\n";
	return s;
}

