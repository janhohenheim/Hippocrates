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

string Gene::GetJSON() const {
	auto BoolToString = [](bool b) {
		return b ? "true" : "false";
	};
	string s("{\"historicalMarking\":");
	s += to_string(historicalMarking);
	s += ",\"from\":";
	s += to_string(from);
	s += ",\"to\":";
	s += to_string(to);
	s += ",\"weight\":";
	s += to_string(weight);
	s += ",\"isEnabled\":";
	s += BoolToString(isEnabled);
	s += ",\"isRecursive\":";
	s += BoolToString(isRecursive);
	s += "}";
	return s;
}

