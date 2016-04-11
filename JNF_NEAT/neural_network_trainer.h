#pragma once
#include "neural_network.h"
#include "trainable.h"
#include "training_parameters.h"
#include "gene_mutator.h"
#include <vector>

class NeuralNetworkTrainer {
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
		GeneMutator geneMutator;

	// Methods
	public:
		NeuralNetworkTrainer() = delete;
        explicit NeuralNetworkTrainer(std::vector<ITrainable *> & population, const TrainingParameters & parameters);
        explicit NeuralNetworkTrainer(std::vector<ITrainable *> & population, TrainingParameters && parameters);

		NeuralNetworkTrainer(const NeuralNetworkTrainer & other) = default;

        ~NeuralNetworkTrainer() = default;


		void TrainUntilFitnessEquals(int fitnessToReach);
		void TrainUntilGenerationEquals(unsigned int generationsToTrain);

		Individuum GetFittestSpecimen();

	private:
		void SetPopulation(std::vector<ITrainable *> & population);
		NeuralNetwork Breed(ITrainable * mother, ITrainable * father);
		void LetGenerationLive();
		void Repopulate();        
};