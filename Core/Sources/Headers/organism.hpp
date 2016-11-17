#pragma once
#include "neural_network.hpp"
#include "body.hpp"
#include "genome.hpp"
#include <memory>

namespace Hippocrates {

class Organism {
private:
	IBody* body = nullptr;
	mutable Type::fitness_t fitness = 0.0;
	mutable bool isFitnessUpToDate = false;
	Type::fitness_t fitnessModifier = 1.0;
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
	auto SetFitnessModifier(Type::fitness_t factor) -> void { fitnessModifier = factor; }
	auto GetOrCalculateFitness() const ->Type::fitness_t;
	auto GetOrCalculateRawFitness() const ->Type::fitness_t;
	auto GetMaxFitness() const { return body->GetMaximumFitness(); }
	auto BreedWith(const Organism& partner, InnovationCacher& currGenerationInnovations) const -> NeuralNetwork;
	auto GetGenome() const -> const Genome&{ return network.GetGenome(); }
	auto GetNeuralNetwork() const -> const NeuralNetwork& {return network; }
	auto HasFinishedTask() const -> bool { return body->HasFinishedTask(); }
	auto GetJSON() const->std::string;
};

}
