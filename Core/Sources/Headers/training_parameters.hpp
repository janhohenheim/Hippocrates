#pragma once
#include <limits>
#include <string>

namespace Hippocrates {

struct TrainingParameters {
	TrainingParameters() = default;
	TrainingParameters(std::string json);

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
		float reproductionThreshold = 0.2f;
		std::size_t minParents = 1;
	} reproduction;
	struct Structure {
		std::size_t numberOfBiasNeurons = 1;
		std::size_t memoryResetsBeforeTotalReset = 0;
		bool allowRecurrentConnections = false;
	} structure;

	auto GetJSON() const -> std::string;
};

}
