#pragma once
#include "neural_network.h"
#include "trainable.h"
#include "training_parameters.h"
#include "gene_mutator.h"
#include <vector>

class NeuralNetworkTrainer {
	private:
		struct Individuum {
            Individuum(ITrainable * trainable, NeuralNetwork && network) :
                trainable(trainable), 
                network(std::move(network)) {}
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

		const Individuum & GetFittestSpecimen();

	private:
		void SetPopulation(std::vector<ITrainable *> & population);
		NeuralNetwork Breed(ITrainable * mother, ITrainable * father);
		unsigned int GetGeneticalDistance(const std::vector<Gene> & leftGenome, const std::vector<Gene> & rightGenome);
		void ResetPopulation();
		void Repopulate();        
		void LetGenerationLive();
};