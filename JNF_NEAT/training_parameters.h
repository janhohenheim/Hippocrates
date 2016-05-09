#pragma once
#include <limits>
struct TrainingParameters {
	unsigned int numberOfInputs = 0U;
	unsigned int numberOfOutputs = 0U;
	unsigned int updatesPerGeneration = 1U;

	struct Advanced {
        struct Ranges {
            int minFitness = std::numeric_limits<int>::min();
            int maxFitness = 100;
            float minNeuralCharge = 0.0f;
            float maxNeuralCharge = 1.0f;
        } ranges;
        struct Mutation {
            float chanceForWeightMutation = 0.8f;
            float chanceForConnectionalMutation = 0.05f;
            float chanceForNeuralMutation = 0.03f;
        } mutation;
        struct Speciation {
            float importanceOfDisjointGenes = 1.0f;
            float importanceOfAverageWeightDifference = 0.3f;
			float compatibilityThreshold = 3.0f;
        } speciation;
		struct Reproduction {
			float chanceForInterspecialReproduction = 0.001f;
		} reproduction;
	} advanced;
};