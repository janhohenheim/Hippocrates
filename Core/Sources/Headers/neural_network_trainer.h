#pragma once
#include "training_parameters.h"
#include "species.h"
#include "trained_neural_network.h"
#include "logger.h"
#include "species_manager.h"
#include "training_data.h"
#include "supervised_training_body.h"
#include <vector>
#include <memory>

namespace JNF_NEAT {

class NeuralNetworkTrainer {
public:
	bool loggingEnabled = false;

private:
	TrainingParameters parameters;
	SpeciesManager species;
	Logger logger;
	size_t generationsPassed = 0;

public:
	explicit NeuralNetworkTrainer(TrainingParameters parameters = TrainingParameters());
	NeuralNetworkTrainer(const NeuralNetworkTrainer& other) = default;
	NeuralNetworkTrainer(NeuralNetworkTrainer&& other) = default;

	auto operator=(const NeuralNetworkTrainer&) -> NeuralNetworkTrainer& = default;
	auto operator=(NeuralNetworkTrainer&&) -> NeuralNetworkTrainer& = default;

	auto TrainUnsupervised(SpeciesManager::Bodies& bodies) -> TrainedNeuralNetwork;
	template <typename InputType, typename Classification, std::size_t ClassificationCount>
	auto TrainSupervised(const TrainingData<InputType, Classification, ClassificationCount>& data, std::size_t trainingInstances) -> TrainedNeuralNetwork;
	auto GetJSON() const -> std::string;

private:
	auto TrainGenerationAndLogUsingBodies(SpeciesManager::Bodies& bodies) -> void;
};

template <typename InputType, typename Classification, std::size_t ClassificationCount>
auto NeuralNetworkTrainer::TrainSupervised(const TrainingData<InputType, Classification, ClassificationCount>& data, std::size_t trainingInstances) -> TrainedNeuralNetwork {
	using Body = SupervisedTrainigBody<InputType, Classification, ClassificationCount>;
	std::vector<Body> bodies;
	bodies.reserve(trainingInstances);
	for (std::size_t i = 0; i < trainingInstances; ++i) {
		Body body(data);
		bodies.push_back(std::move(body));
	}
	SpeciesManager::Bodies bodyRefs(bodies.begin(), bodies.end());
	return TrainUnsupervised(bodyRefs);
}

}
