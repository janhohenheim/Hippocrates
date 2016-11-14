#ifdef _WIN32
	#define SSCANF sscanf_s
#else
	#define SSCANF sscanf
#endif

#include <iostream>
#include "../Headers/training_parameters.hpp"
#include "../Headers/jsmn.h"

using namespace Hippocrates;
using namespace std;

TrainingParameters::TrainingParameters(std::string json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	auto token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (size_t i = 0; i < token_count - 1; i++) {
		auto key = json.substr(tokens[i].start, tokens[i].end - tokens[i].start);
		auto value = json.substr(tokens[i + 1].start, tokens[i + 1].end - tokens[i + 1].start);

		if (key == "minWeight") {
			ranges.minWeight = stof(value);
		} else
		if (key == "maxWeight") {
			ranges.maxWeight = stof(value);
		} else
		if (key == "chanceForWeightMutation") {
			mutation.chanceForWeightMutation = stof(value);
		} else
		if (key == "chanceForConnectionalMutation") {
			mutation.chanceForConnectionalMutation = stof(value);
		} else
		if (key == "chanceForNeuralMutation") {
			mutation.chanceForNeuralMutation = stof(value);
		} else
		if (key == "chanceOfTotalWeightReset") {
			mutation.chanceOfTotalWeightReset = stof(value);
		} else
		if (key == "importanceOfDisjointGenes") {
			speciation.importanceOfDisjointGenes = stof(value);
		} else
		if (key == "importanceOfAverageWeightDifference") {
			speciation.importanceOfAverageWeightDifference = stof(value);
		} else
		if (key == "compatibilityThreshold") {
			speciation.compatibilityThreshold = stof(value);
		} else
		if (key == "stagnantSpeciesClearThreshold") {
			SSCANF(value.c_str(), "%zu", &speciation.stagnantSpeciesClearThreshold);
		} else
		if (key == "normalizeForLargerGenome") {
			speciation.normalizeForLargerGenome = value == "true";
		} else
		if (key == "chanceForInterspecialReproduction") {
			reproduction.chanceForInterspecialReproduction = stof(value);
		} else
		if (key == "minSpeciesSizeForChampConservation") {
			SSCANF(value.c_str(), "%zu", &reproduction.minSpeciesSizeForChampConservation);
		} else
		if (key == "reproductionThreshold") {
			reproduction.reproductionThreshold = stof(value);
		} else
		if (key == "minParents") {
			SSCANF(value.c_str(), "%zu", &reproduction.minParents);
		} else
		if (key == "numberOfBiasNeurons") {
			SSCANF(value.c_str(), "%zu", &structure.numberOfBiasNeurons);
		} else
		if (key == "allowRecurrentConnections") {
			structure.allowRecurrentConnections = value == "true";
		}
	}
}

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
	s += ",\"reproductionThreshold\":";
	s += to_string(reproduction.reproductionThreshold);
	s += ",\"minParents\":";
	s += to_string(reproduction.minParents);
	s += "}";

	s += ",\"structure\":";
	s += "{";
	s += "\"numberOfBiasNeurons\":";
	s += to_string(structure.numberOfBiasNeurons);
	s += ",\"allowRecurrentConnections\":";
	s += BoolToString(structure.allowRecurrentConnections);
	s += "}";

	s += "}";

	return s;
}
