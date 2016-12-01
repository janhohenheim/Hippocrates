#include <iostream>

#include "training/parameters.hpp"
#include "utility/jsmn.h"

using namespace Hippocrates;
using namespace Hippocrates::Training;

Parameters::Parameters(const std::string& json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	std::size_t token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (std::size_t i = 0; i < token_count - 1; i++) {
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
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &speciation.stagnantSpeciesClearThreshold);
		} else
		if (key == "normalizeForLargerGenome") {
			speciation.normalizeForLargerGenome = value == "true";
		} else
		if (key == "chanceForInterspecialReproduction") {
			reproduction.chanceForInterspecialReproduction = stof(value);
		} else
		if (key == "minSpeciesSizeForChampConservation") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &reproduction.minSpeciesSizeForChampConservation);
		} else
		if (key == "reproductionThreshold") {
			reproduction.reproductionThreshold = stof(value);
		} else
		if (key == "minParents") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &reproduction.minParents);
		} else
		if (key == "numberOfBiasNeurons") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &structure.numberOfBiasNeurons);
		} else
		if (key == "allowRecurrentConnections") {
			structure.allowRecurrentConnections = value == "true";
		}
	}
}

auto Parameters::GetJSON() const -> std::string {
	auto BoolToString = [](bool b) {
		return b ? "true" : "false";
	};
	
	std::string s("{");

	s += "\"ranges\":";
	s += "{";
	s += "\"minWeight\":";
	s += std::to_string(ranges.minWeight);
	s += ",\"maxWeight\":";
	s += std::to_string(ranges.maxWeight);
	s += "}";

	s += ",\"mutation\":";
	s += "{";
	s += "\"chanceForWeightMutation\":";
	s += std::to_string(mutation.chanceForWeightMutation);
	s += ",\"chanceForConnectionalMutation\":";
	s += std::to_string(mutation.chanceForConnectionalMutation);
	s += ",\"chanceForNeuralMutation\":";
	s += std::to_string(mutation.chanceForNeuralMutation);
	s += ",\"chanceOfTotalWeightReset\":";
	s += std::to_string(mutation.chanceOfTotalWeightReset);
	s += "}";

	s += ",\"speciation\":";
	s += "{";
	s += "\"importanceOfDisjointGenes\":";
	s += std::to_string(speciation.importanceOfDisjointGenes);
	s += ",\"importanceOfAverageWeightDifference\":";
	s += std::to_string(speciation.importanceOfAverageWeightDifference);
	s += ",\"compatibilityThreshold\":";
	s += std::to_string(speciation.compatibilityThreshold);
	s += ",\"stagnantSpeciesClearThreshold\":";
	s += std::to_string(speciation.stagnantSpeciesClearThreshold);
	s += ",\"normalizeForLargerGenome\":";
	s += BoolToString(speciation.normalizeForLargerGenome);
	s += "}";

	s += ",\"reproduction\":";
	s += "{";
	s += "\"chanceForInterspecialReproduction\":";
	s += std::to_string(reproduction.chanceForInterspecialReproduction);
	s += ",\"minSpeciesSizeForChampConservation\":";
	s += std::to_string(reproduction.minSpeciesSizeForChampConservation);
	s += ",\"reproductionThreshold\":";
	s += std::to_string(reproduction.reproductionThreshold);
	s += ",\"minParents\":";
	s += std::to_string(reproduction.minParents);
	s += "}";

	s += ",\"structure\":";
	s += "{";
	s += "\"numberOfBiasNeurons\":";
	s += std::to_string(structure.numberOfBiasNeurons);
	s += ",\"allowRecurrentConnections\":";
	s += BoolToString(structure.allowRecurrentConnections);
	s += "}";

	s += "}";

	return s;
}
