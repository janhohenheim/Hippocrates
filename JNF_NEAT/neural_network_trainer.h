#pragma once
#include "neural_network.h"
#include "body.h"
#include "training_parameters.h"
#include "genome.h"
#include "organism.h"
#include "species.h"
#include "trained_neural_network.h"
#include <vector>
#include <list>

namespace JNF_NEAT {

	class NeuralNetworkTrainer {
		private:
			std::vector<Species> species;
			TrainingParameters parameters;
			size_t populationSize = 0U;
			std::vector<IBody *>& bodies;
			size_t generationsPassed = 0;

		public:
			NeuralNetworkTrainer() = delete;
			NeuralNetworkTrainer(std::vector<IBody*>& population, TrainingParameters parameters);
			NeuralNetworkTrainer(const NeuralNetworkTrainer& other) = default;

			~NeuralNetworkTrainer() = default;

			void TrainUntilFitnessEquals(double fitnessToReach);
			void TrainUntilGenerationEquals(unsigned int generationsToTrain);

			TrainedNeuralNetwork GetTrainedNeuralNetwork();
			std::string ToString () const;
		private:
			void SetBodies(std::vector<IBody*>& bodies);

			void ResetPopulationToTeachableState();
			void Repopulate();
			void LetGenerationLive();
			void PrepareSpeciesForPopulation();
			void FillOrganismIntoSpecies(const Organism& organism);
			void FillOrganismIntoSpecies(Organism&& organism);
			void AnalyzeAndClearSpeciesPopulation();
			void DeleteStagnantSpecies();
			void DeleteEmptySpecies();

			Species& SelectSpeciesToBreed();
			Organism& GetFittestOrganism();
	};

}