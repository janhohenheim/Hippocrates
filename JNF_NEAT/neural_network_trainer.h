#pragma once
#include "neural_network.h"
#include "trainable.h"
#include <vector>
#include <limits>

class NeuralNetworkTrainer {
	// Members
	public:
		struct TrainingParameters {
			unsigned int numberOfInputs = 0U;
			unsigned int numberOfOutputs = 0U;
			struct Ruleset {
				int minFitness = std::numeric_limits<int>::min();
				int maxFitness = 100;
				unsigned int updatesPerGeneration = 1U;
				float minNeuralCharge = 0.0;
				float maxNeuralCharge = 1.0;
				// TODO jnf
				// change to sensible values
				float chanceForWeightMutation = 1.0;
				float chanceForConnectionalMutation = 1.0;
				float chanceForNeuralMutation = 1.0;
			} ruleset;
		};
	private:
		struct Individuum {
			ITrainable * trainable = nullptr;
			NeuralNetwork network;
		};
		std::vector <Individuum> population;
		TrainingParameters parameters;

	// Methods
	public:
		explicit NeuralNetworkTrainer(TrainingParameters parameters);
		NeuralNetworkTrainer(const NeuralNetworkTrainer & other) = default;
		~NeuralNetworkTrainer() = default;

		void SetPopulation(std::vector<ITrainable *> & population);

		void TrainUntilFitnessEquals(int fitnessToReach);
		void TrainUntilGenerationEquals(unsigned int generationsToTrain);

		Individuum GetFittestSpecimen();

	private:
		NeuralNetwork Breed(ITrainable * mother, ITrainable * father);
		void LetGenerationLive();
		void Repopulate();
		bool ShouldMutate();
		void MutateGenes(std::vector<Gene> & genes);
};