#include "gene.h"
#include <stdlib.h>
#include <sstream>

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

void Gene::ExportJSON(ostream& output) const {
	auto BoolToString = [](bool b) {
		return b ? "true" : "false";
	};
	stringstream s;
	s << "{\"historicalMarking\":" << historicalMarking << ","
		<< "\"from\":" << from << ","
		<< "\"to\":" << to << ","
		<< "\"weight\":" << weight << ","
		<< "\"isEnabled\":" << BoolToString(isEnabled) << ","
		<< "\"isRecursive\":" << BoolToString(isRecursive) << "}";
	output << s.rdbuf();
}

