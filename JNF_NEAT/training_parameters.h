#pragma once
#include <limits>
#include <string>

namespace JNF_NEAT {

struct TrainingParameters {
	TrainingParameters(unsigned int numberOfInputs, unsigned int numberOfOutputs) :
		numberOfInputs(numberOfInputs), numberOfOutputs(numberOfOutputs) {}
	unsigned int numberOfInputs = 0U;
	unsigned int numberOfOutputs = 0U;

	struct Advanced {
		struct Ranges {
			float minWeight = -1.0f;
			float maxWeight = 1.0f;
		} ranges;
		struct Mutation {
			float chanceForWeightMutation = 0.8f;
			float chanceForConnectionalMutation = 0.05f;
			float chanceForNeuralMutation = 0.03f;
			float chanceOfTotalWeightReset = 0.1f;
		} mutation;
		struct Speciation {
			float importanceOfDisjointGenes = 1.0f;
			float importanceOfAverageWeightDifference = 2.0f;
			float compatibilityThreshold = 3.0f;
			std::size_t stagnantSpeciesClearThreshold = 15;
			bool normalizeForLargerGenome = false;
		} speciation;
		struct Reproduction {
			float chanceForInterspecialReproduction = 0.001f;
			std::size_t minSpeciesSizeForChampConservation = 5;
		} reproduction;
		struct Structure {
			std::size_t numberOfBiasNeurons = 1;
		} structure;
	} advanced;

	auto GetJSON() const -> std::string {
		std::string s("{");
		s += "\"numberOfInputs\":";
		s += std::to_string(numberOfInputs);
		s += ",\"numberOfOutputs\":";
		s += std::to_string(numberOfOutputs);

		s += ",\"advanced\":";
		s += "{";

		s += ",\"ranges\":";
		s += "{";
		s += ",\"minWeight\":";
		s += std::to_string(advanced.ranges.minWeight);
		s += ",\"maxWeight\":";
		s += std::to_string(advanced.ranges.maxWeight);
		s += "}";
		// etc.
        // Todo sara: append the rest of the members to the string

		s += "}";

		s += "}";

		return s;
	}
};

}
