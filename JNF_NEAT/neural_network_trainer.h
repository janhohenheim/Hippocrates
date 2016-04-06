#pragma once
#include "neural_network.h"
#include "trainable.h"
#include <vector>
#include <limits>

class NeuralNetworkTrainer {
	// Members
	public:
		struct Ruleset {
			int minFitness = std::numeric_limits<int>::min();
			int maxFitness = 100;
			unsigned int updatesPerGeneration = 1;
			float minNeuralCharge = 0.0;
			float maxNeuralCharge = 1.0;
		};

	private:
		std::vector <ITrainable *> & population;
		Ruleset ruleset;

	// Methods
	public:
		NeuralNetworkTrainer(std::vector<ITrainable *> & population);
		NeuralNetworkTrainer(std::vector<ITrainable *> & population, Ruleset ruleset);
		NeuralNetworkTrainer(const NeuralNetworkTrainer & other) = default;
		~NeuralNetworkTrainer() = default;

		void TrainUntilFitnessEquals(int fitnessToReach);
		void TrainUntilGenerationEquals(unsigned int generationsToTrain);

		ITrainable * GetFittestSpecimen();

	private:
		NeuralNetwork Breed(ITrainable * mother, ITrainable * father) const;
		void LetGenerationLive();
		void Repopulate();
		void MutateGenes(std::vector<Gene> & genes) const;
};