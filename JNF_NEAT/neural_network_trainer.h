#pragma once
#include "neural_network.h"
#include "network_trainer.h"
#include "training_parameters.h"
#include "genome.h"
#include "organism.h"
#include "species.h"
#include <vector>
#include <list>

class NeuralNetworkTrainer {
	private:
		std::vector<Species> species;
		TrainingParameters parameters;
		size_t populationSize = 0U;
		std::vector<INetworkTrainer *>& trainers;

	public:
		NeuralNetworkTrainer() = delete;
        NeuralNetworkTrainer(std::vector<INetworkTrainer*>& population, const TrainingParameters& parameters);
        NeuralNetworkTrainer(std::vector<INetworkTrainer*>& population, TrainingParameters&& parameters);
		NeuralNetworkTrainer(const NeuralNetworkTrainer& other) = default;

        ~NeuralNetworkTrainer() = default;


		void TrainUntilFitnessEquals(int fitnessToReach);
		void TrainUntilGenerationEquals(unsigned int generationsToTrain);

		Organism& GetFittestSpecimen();

	private:
		void SetPopulation(std::vector<INetworkTrainer*>& population);
		
		void ResetPopulationToTeachableState();
		void Repopulate();
        void CategorizeOrganismsIntoSpecies(std::vector<Organism> && organisms);
		void LetGenerationLive();

	Species &SelectSpeciesToBreed();
};