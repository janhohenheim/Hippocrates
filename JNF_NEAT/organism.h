#pragma once
#include "neural_network.h"
#include "body.h"
#include "training_parameters.h"
#include "genome.h"

namespace JNF_NEAT {

	class Organism {
		private:
			IBody* body = nullptr;
			NeuralNetwork network;
			double fitness = 0.0;
			double fitnessModifier = 1.0;
			bool isFitnessUpToDate = false;

		public:
			Organism(IBody* body, NeuralNetwork&& network);
			Organism(IBody* body, const NeuralNetwork&& network) = delete;
			Organism(const Organism& other) = default;
			Organism(Organism&& other) = default;
			~Organism() = default;

			Organism& operator=(const Organism& other) = default;

			void Reset() { body->Reset(); }
			void Update();
			void SetFitnessModifier(double factor) { fitnessModifier = factor; }
			double GetOrCalculateFitness();
			double GetOrCalculateRawFitness();
			NeuralNetwork BreedWith(Organism& partner);
			const Genome& GetGenome() const { return network.GetGenome(); }
			const NeuralNetwork & GetNetwork() const { return network; }
			const TrainingParameters& GetTrainingParameters() const { return network.GetTrainingParameters(); }
			void ExportJSON(std::ostream& output) const;
	};

}