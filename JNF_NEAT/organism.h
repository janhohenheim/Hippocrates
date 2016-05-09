#pragma once
#include "neural_network.h"
#include "trainable.h"
#include "training_parameters.h"
#include "genome.h"

class Organism {
	private:
		ITrainable* trainable = nullptr;
		NeuralNetwork network;
		int fitness = 0;
		bool isFitnessUpToDate = false;

	public:
		Organism(ITrainable* trainable, NeuralNetwork&& network);
		Organism(ITrainable* trainable, const NeuralNetwork&& network) = delete;
		Organism(const Organism& other) = default;
		Organism(Organism&& other) = default;
		~Organism() = default;

		Organism& operator=(const Organism& other) = default;


		void Reset() { trainable->Reset(); }
		void Update();
		void ModifyFitness(float factor);
		int GetOrCalculateFitness();
		Genome BreedWith(Organism& partner);
		const Genome& GetGenome() const { return network.GetGenome(); }
        ITrainable * GetTrainable() const { return trainable; }
};