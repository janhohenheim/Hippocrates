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
			neural.minWeight = stof(value);
		} else
		if (key == "maxWeight") {
			neural.maxWeight = stof(value);
		} else
		if (key == "activationFunction"){
			std::size_t asNr;
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &asNr);
			neural.activationFunction = static_cast<ActivationFunction::PossibleActivationFunctions>(asNr);
		}
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

std::ostream & Hippocrates::Training::operator<<(std::ostream & stream, const Parameters & parameters)
{
	auto BoolToString = [](bool b) {
		return b ? "true" : "false";
	};

	stream << "{" <<

	"\"neural\":" <<
	"{" <<
	"\"minWeight\":" <<
	std::to_string(parameters.neural.minWeight) <<
	",\"maxWeight\":" <<
	std::to_string(parameters.neural.maxWeight) <<
	",\"activationFunction\":" <<
	static_cast<std::size_t>(parameters.neural.activationFunction) <<
	"}" <<

	",\"mutation\":" <<
	"{" <<
	"\"chanceForWeightMutation\":" <<
	std::to_string(parameters.mutation.chanceForWeightMutation) <<
	",\"chanceForConnectionalMutation\":" <<
	std::to_string(parameters.mutation.chanceForConnectionalMutation) <<
	",\"chanceForNeuralMutation\":" <<
	std::to_string(parameters.mutation.chanceForNeuralMutation) <<
	",\"chanceOfTotalWeightReset\":" <<
	std::to_string(parameters.mutation.chanceOfTotalWeightReset) <<
	"}" <<

	",\"speciation\":" <<
	"{" <<
	"\"importanceOfDisjointGenes\":" <<
	std::to_string(parameters.speciation.importanceOfDisjointGenes) <<
	",\"importanceOfAverageWeightDifference\":" <<
	std::to_string(parameters.speciation.importanceOfAverageWeightDifference) <<
	",\"compatibilityThreshold\":" <<
	std::to_string(parameters.speciation.compatibilityThreshold) <<
	",\"stagnantSpeciesClearThreshold\":" <<
	std::to_string(parameters.speciation.stagnantSpeciesClearThreshold) <<
	",\"normalizeForLargerGenome\":" <<
	BoolToString(parameters.speciation.normalizeForLargerGenome) <<
	"}" <<

	",\"reproduction\":" <<
	"{" <<
	"\"chanceForInterspecialReproduction\":" <<
	std::to_string(parameters.reproduction.chanceForInterspecialReproduction) <<
	",\"minSpeciesSizeForChampConservation\":" <<
	std::to_string(parameters.reproduction.minSpeciesSizeForChampConservation) <<
	",\"reproductionThreshold\":" <<
	std::to_string(parameters.reproduction.reproductionThreshold) <<
	",\"minParents\":" <<
	std::to_string(parameters.reproduction.minParents) <<
	"}" <<

	",\"structure\":" <<
	"{" <<
	"\"numberOfBiasNeurons\":" <<
	std::to_string(parameters.structure.numberOfBiasNeurons) <<
	",\"allowRecurrentConnections\":" <<
	BoolToString(parameters.structure.allowRecurrentConnections) <<
	"}" <<

	"}";

	return stream;
}
