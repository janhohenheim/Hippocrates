#pragma once
#include <limits>

namespace JNF_NEAT {

	struct TrainingParameters {
		unsigned int numberOfInputs = 0U;
		unsigned int numberOfOutputs = 0U;
		unsigned int updatesPerGeneration = 1U;

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
	};

}