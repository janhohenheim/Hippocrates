#pragma once
#include "neural_network.h"
#include "trainable.h"
#include <vector>

class NeuralNetworkTrainer {
	private:
		std::vector <ITrainable *> & population;

	public:
		NeuralNetworkTrainer(std::vector<ITrainable *> & population);
		NeuralNetworkTrainer(const NeuralNetworkTrainer & other) = default;
		~NeuralNetworkTrainer() = default;

		void TrainUntilFitnessEquals(unsigned int fitnessToReach);
		void TrainUntilGenerationEquals(unsigned int generationsToTrain);

		const ITrainable * GetFittestSpecimen();

	private:
		NeuralNetwork Breed(const ITrainable * mother, const ITrainable * father) const;
		void LetGenerationLive();
		void Repopulate();
		void MutateGenes(std::vector<Gene> & genes) const;
};