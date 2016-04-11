#pragma once
#include <limits>
struct TrainingParameters {
	unsigned int numberOfInputs = 0U;
	unsigned int numberOfOutputs = 0U;

	struct Ruleset {
		int minFitness = std::numeric_limits<int>::min();
		int maxFitness = 100;
		unsigned int updatesPerGeneration = 1U;
		float minNeuralCharge = 0.0f;
		float maxNeuralCharge = 1.0f;
		float chanceForWeightMutation = 0.8f;
		float chanceForConnectionalMutation = 0.05f;
		float chanceForNeuralMutation = 0.03f;
	} ruleset;
};