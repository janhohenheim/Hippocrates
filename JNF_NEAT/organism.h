#pragma once
#include "neural_network.h"
#include "body.h"
#include "training_parameters.h"
#include "genome.h"
#include <memory>

namespace JNF_NEAT {

class Organism {
private:
	std::shared_ptr<IBody> body;
	NeuralNetwork network;
	mutable double fitness = 0.0;
	double fitnessModifier = 1.0;
	mutable bool isFitnessUpToDate = false;

public:
	Organism(std::shared_ptr<IBody> body, NeuralNetwork&& network);
	Organism(const Organism& other) = default;
	Organism(Organism&& other) = default;
	~Organism() = default;

	auto operator=(const Organism& other) -> Organism& = default;
	auto operator=(Organism&& other) -> Organism& = default;

	auto Reset() -> void { body->Reset(); }
	auto Update() -> void;
	auto SetFitnessModifier(double factor) -> void { fitnessModifier = factor; }
	auto GetOrCalculateFitness() const -> double;
	auto GetOrCalculateRawFitness() const -> double;
	auto BreedWith(Organism& partner) -> NeuralNetwork;
	auto GetGenome() const -> const Genome&{ return network.GetGenome(); }
	auto HasFinishedTask() const -> bool { return body->HasFinishedTask(); }
	auto GetTrainingParameters() const -> const TrainingParameters&{ return network.GetTrainingParameters(); }
	auto GetJSON() const->std::string;
};

}
