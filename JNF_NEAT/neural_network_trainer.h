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
            Individuum(ITrainable * trainable, const NeuralNetwork & network) :
                trainable(trainable), 
                network(network) {}
			ITrainable * trainable = nullptr;
			NeuralNetwork network;
		};
		std::vector <Individuum> population;
		TrainingParameters parameters;

	// Methods
	public:
        explicit NeuralNetworkTrainer(const TrainingParameters & parameters);
        explicit NeuralNetworkTrainer(TrainingParameters && parameters);
        NeuralNetworkTrainer(const TrainingParameters && parameters) = delete;

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

        void MaybeMutateGenes(std::vector<Gene> & genes);
        static bool DidChanceOccure(float chance);

        bool ShouldMutateWeights() const { return DidChanceOccure(parameters.ruleset.chanceForWeightMutation); }
        bool ShouldAddNeuron() const { return DidChanceOccure(parameters.ruleset.chanceForNeuralMutation); }
        bool ShouldAddConnection() const { return DidChanceOccure(parameters.ruleset.chanceForConnectionalMutation); }
		void MutateWeights(std::vector<Gene> & genes);
        void AddRandomNeuron(std::vector<Gene> & genes);
        void AddRandomConnection(std::vector<Gene> & genes);
};