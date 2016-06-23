#pragma once
#include "neural_network.h"
#include "body.h"
#include "training_parameters.h"
#include "genome.h"
#include "organism.h"
#include "species.h"
#include "trained_neural_network.h"
#include <vector>
#include <chrono>
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

		public:
			NeuralNetworkTrainer() = delete;
			NeuralNetworkTrainer(std::vector<std::shared_ptr<IBody>> population, TrainingParameters parameters);
			NeuralNetworkTrainer(const NeuralNetworkTrainer& other) = default;

			~NeuralNetworkTrainer() = default;

			void TrainUntilFitnessEquals(double fitnessToReach);
			void TrainUntilGenerationEquals(size_t generationsToTrain);
			TrainedNeuralNetwork GetTrainedNeuralNetwork();
			std::string GetJSON() const;

		private:
			void CreateInitialOrganisms();
			void TrainGeneration();
			void LogCurrentGeneration();
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
			std::chrono::system_clock::time_point trainingStart;
			static constexpr auto logFolder = L"/json_dumps/";
			static constexpr auto logFileExtension = L".json";
	};
}