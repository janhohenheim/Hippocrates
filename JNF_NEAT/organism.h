#pragma once
#include "neural_network.h"
#include "body.h"
#include "training_parameters.h"
#include "genome.h"

class Organism {
	private:
		IBody* trainer = nullptr;
		NeuralNetwork network;
		int fitness = 0;
		float fitnessModifier = 0.0f;
		bool isFitnessUpToDate = false;

	public:
		Organism(IBody* trainer, NeuralNetwork&& network);
		Organism(IBody* trainer, const NeuralNetwork&& network) = delete;
		Organism(const Organism& other) = default;
		Organism(Organism&& other) = default;
		~Organism() = default;

		Organism& operator=(const Organism& other) = default;

		void Reset() { trainer->Reset(); }
		void Update();
		void SetFitnessModifier(float factor) {fitnessModifier = factor;}
		int GetOrCalculateFitness();
		NeuralNetwork BreedWith(Organism& partner);
		const Genome& GetGenome() const { return network.GetGenome(); }
		const NeuralNetwork & GetNetwork() const {return network; }
};