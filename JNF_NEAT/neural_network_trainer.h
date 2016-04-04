#pragma once
#include "neural_network.h"
#include "i_specimen.h"
#include <vector>

class NeuralNetworkTrainer {
	public:
		NeuralNetworkTrainer(std::vector<ISpecimen*> & population);
		NeuralNetworkTrainer(const NeuralNetworkTrainer & other) = default;
		~NeuralNetworkTrainer() = default;

		void TrainUntilFitnessEquals(unsigned int fitnessToReach);
		void TrainUntilGenerationEquals(unsigned int generationsToTrain);

		const ISpecimen * GetFittestSpecimen();
	private:
		NeuralNetwork Breed(const ISpecimen * mother, const ISpecimen * father) const;


	private:
		std::vector <ISpecimen *> & population;
};
