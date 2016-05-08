#pragma once
#include "neural_network.h"
#include "trainable.h"
#include "training_parameters.h"
#include "genome.h"
#include "individual.h"
#include "species.h"
#include <vector>
#include <list>

class NeuralNetworkTrainer {
	private:
		std::vector<Individual> population;
		std::vector<Species> species;
		TrainingParameters parameters;

	public:
		NeuralNetworkTrainer() = delete;
        NeuralNetworkTrainer(std::vector<ITrainable*>& population, const TrainingParameters& parameters);
        NeuralNetworkTrainer(std::vector<ITrainable*>& population, TrainingParameters&& parameters);
		NeuralNetworkTrainer(const NeuralNetworkTrainer& other) = default;

        ~NeuralNetworkTrainer() = default;


		void TrainUntilFitnessEquals(int fitnessToReach);
		void TrainUntilGenerationEquals(unsigned int generationsToTrain);

		Individual& GetFittestSpecimen();

	private:
		void SetPopulation(std::vector<ITrainable*>& population);
		
		void ResetPopulationToTeachableState();
		void Repopulate();        
        Individual & SelectIndividualToBreed();
        void CategorizePopulationIntoSpecies();
		void LetGenerationLive();
};