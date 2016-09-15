#include "training_parameters.h"
using namespace JNF_NEAT;
using namespace std;

auto TrainingParameters::GetJSON() const -> std::string {
	auto BoolToString = [](bool b) {
		return b ? "true" : "false";
	};
	
	string s("{");

	s += "\"ranges\":";
	s += "{";
	s += "\"minWeight\":";
	s += to_string(ranges.minWeight);
	s += ",\"maxWeight\":";
	s += to_string(ranges.maxWeight);
	s += "}";

	s += ",\"mutation\":";
	s += "{";
	s += "\"chanceForWeightMutation\":";
	s += to_string(mutation.chanceForWeightMutation);
	s += ",\"chanceForConnectionalMutation\":";
	s += to_string(mutation.chanceForConnectionalMutation);
	s += ",\"chanceForNeuralMutation\":";
	s += to_string(mutation.chanceForNeuralMutation);
	s += ",\"chanceOfTotalWeightReset\":";
	s += to_string(mutation.chanceOfTotalWeightReset);
	s += "}";

	s += ",\"speciation\":";
	s += "{";
	s += "\"importanceOfDisjointGenes\":";
	s += to_string(speciation.importanceOfDisjointGenes);
	s += ",\"importanceOfAverageWeightDifference\":";
	s += to_string(speciation.importanceOfAverageWeightDifference);
	s += ",\"compatibilityThreshold\":";
	s += to_string(speciation.compatibilityThreshold);
	s += ",\"stagnantSpeciesClearThreshold\":";
	s += to_string(speciation.stagnantSpeciesClearThreshold);
	s += ",\"normalizeForLargerGenome\":";
	s += BoolToString(speciation.normalizeForLargerGenome);
	s += "}";

	s += ",\"reproduction\":";
	s += "{";
	s += "\"chanceForInterspecialReproduction\":";
	s += to_string(reproduction.chanceForInterspecialReproduction);
	s += ",\"minSpeciesSizeForChampConservation\":";
	s += to_string(reproduction.minSpeciesSizeForChampConservation);
	s += "}";

	s += ",\"structure\":";
	s += "{";
	s += "\"numberOfBiasNeurons\":";
	s += to_string(structure.numberOfBiasNeurons);
	s += ",\"minSpeciesSizeForChampConservation\":";
	s += BoolToString(structure.areRecursiveConnectionsAllowed);
	s += "}";

	s += "}";

	return s;
}
