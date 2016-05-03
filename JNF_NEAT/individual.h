#pragma once
#include "neural_network.h"
#include "trainable.h"
#include "training_parameters.h"
#include "species.h"
#include "genome.h"

class Individual {
	private:
		ITrainable* trainable = nullptr;
		NeuralNetwork network;
		int fitness = 0;
		bool isFitnessUpToDate = false;
		const Species* species;
		const TrainingParameters& parameters;

	public:
		Individual(ITrainable* trainable, const TrainingParameters& parameters);
		Individual(ITrainable* trainable, const TrainingParameters& parameters, NeuralNetwork&& network);
		Individual(ITrainable* trainable, const NeuralNetwork&& network) = delete;
		Individual(const Individual& other) = default;
		Individual(Individual&& other) = default;
		~Individual() = default;

		Individual& operator=(const Individual& other) = default;


		void Reset() { trainable->Reset(); }
		void Update();
		void ModifyFitness(float factor);
		int GetOrCalculateFitness();
		void CoupleWithSpecies(Species& species);
        NeuralNetwork BreedWith(Individual* partner);
		const Genome& GetGenome() const { return network.GetGenome(); }
};