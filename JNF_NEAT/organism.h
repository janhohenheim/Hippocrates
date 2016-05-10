#pragma once
#include "neural_network.h"
#include "network_trainer.h"
#include "training_parameters.h"
#include "genome.h"

class Organism {
	private:
		INetworkTrainer* trainable = nullptr;
		NeuralNetwork network;
		int fitness = 0;
		float fitnessModifier = 0.0f;
		bool isFitnessUpToDate = false;

	public:
		Organism(INetworkTrainer* trainable, NeuralNetwork&& network);
		Organism(INetworkTrainer* trainable, const NeuralNetwork&& network) = delete;
		Organism(const Organism& other) = default;
		Organism(Organism&& other) = default;
		~Organism() = default;

		Organism& operator=(const Organism& other) = default;


		void Reset() { trainable->Reset(); }
		void Update();
		void SetFitnessModifier(float factor) {fitnessModifier = factor;}
		int GetOrCalculateFitness();
		Genome BreedWith(Organism& partner);
		const Genome& GetGenome() const { return network.GetGenome(); }
};