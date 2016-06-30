#pragma once
#include "neural_network.h"
#include "body.h"
#include "training_parameters.h"
#include "genome.h"
#include "organism.h"
#include "species.h"
#include "trained_neural_network.h"
#include "logger.h"
#include <vector>
#include <memory>

namespace JNF_NEAT {

	class NeuralNetworkTrainer {
		public:
			bool loggingEnabled = false;

		private:
			std::vector<Species> species;
			TrainingParameters parameters;
			size_t populationSize = 0U;
			std::vector<std::shared_ptr<IBody>> bodies;
			size_t generationsPassed = 0;
			Logger logger;

		public:
			NeuralNetworkTrainer(std::vector<std::shared_ptr<IBody>> population, TrainingParameters parameters);
			NeuralNetworkTrainer(const NeuralNetworkTrainer& other) = default;
			NeuralNetworkTrainer(NeuralNetworkTrainer&& other) = default;
			~NeuralNetworkTrainer() = default;
			NeuralNetworkTrainer& operator=(const NeuralNetworkTrainer&) = default;
			NeuralNetworkTrainer& operator=(NeuralNetworkTrainer&&) = default;

			void TrainUntilFitnessEquals(double fitnessToReach);
			void TrainUntilGenerationEquals(size_t generationsToTrain);
			TrainedNeuralNetwork GetTrainedNeuralNetwork();
			std::string GetJSON() const;

		private:
			void CreateInitialOrganisms();
			void TrainGenerationAndLog();
			
			void ResetPopulationToTeachableState();
			void Repopulate();
			void LetGenerationLive();
			void PrepareSpeciesForPopulation();
			void FillOrganismIntoSpecies(Organism&& organism);
			void AnalyzeAndClearSpeciesPopulation();
			void DeleteStagnantSpecies();
			void DeleteEmptySpecies();

			Species& SelectSpeciesToBreed();
			Organism& GetFittestOrganism();		
	};
}