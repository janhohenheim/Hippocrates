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

	auto TrainUnsupervised(const SpeciesManager::Bodies& bodies) -> TrainedNeuralNetwork;
	template <typename InputType, typename Classification, std::size_t ClassificationCount>
	auto TrainSupervised(const TrainingData<InputType, Classification, ClassificationCount>& data, std::size_t trainingInstances) -> TrainedNeuralNetwork;
	auto GetJSON() const -> std::string;

private:
	auto TrainGenerationAndLogUsingBodies(const SpeciesManager::Bodies& bodies) -> void;
};

template <typename InputType, typename Classification, std::size_t ClassificationCount>
auto NeuralNetworkTrainer::TrainSupervised(const TrainingData<InputType, Classification, ClassificationCount>& data, std::size_t trainingInstances) -> TrainedNeuralNetwork {
	SpeciesManager::Bodies bodies;
	bodies.reserve(trainingInstances);
	for (std::size_t i = 0; i < trainingInstances; ++i) {
		using Body = SupervisedTrainigBody<InputType, Classification, ClassificationCount>;
		Body body(data);
		bodies.push_back(std::make_shared<Body>(std::move(body)));
	}
	return TrainUnsupervised(bodies);
}

}
