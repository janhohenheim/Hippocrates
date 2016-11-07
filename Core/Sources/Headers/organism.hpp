#pragma once
#include "neural_network.hpp"
#include "body.hpp"
#include "training_parameters.hpp"
#include "genome.hpp"
#include <memory>

namespace Hippocrates {

class Organism {
private:
	IBody* body = nullptr;
	mutable double fitness = 0.0;
	mutable bool isFitnessUpToDate = false;
	double fitnessModifier = 1.0;
	NeuralNetwork network;

public:
	Organism(IBody& body, NeuralNetwork&& network);
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
	auto GetMaxFitness() const { return body->GetMaximumFitness(); }
	auto BreedWith(const Organism& partner) const -> NeuralNetwork;
	auto GetGenome() const -> const Genome&{ return network.GetGenome(); }
	auto GetNeuralNetwork() const -> const NeuralNetwork& {return network; }
	auto HasFinishedTask() const -> bool { return body->HasFinishedTask(); }
	auto GetTrainingParameters() const -> const TrainingParameters&{ return network.GetTrainingParameters(); }
	auto GetJSON() const->std::string;
};

}
