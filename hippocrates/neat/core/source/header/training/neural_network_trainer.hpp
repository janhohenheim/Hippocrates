#pragma once
#include "species.hpp"
#include "species_manager.hpp"
#include "data.hpp"
#include "trained/neural_network.hpp"
#include "trained/classifier.hpp"
#include "utility/logger.hpp"
#include "body/supervised_learning.hpp"


#include <vector>
#include <memory>

namespace Hippocrates::Training {

class NeuralNetworkTrainer {
public:
	bool loggingEnabled = false;

private:
	SpeciesManager species;
	Utility::Logger logger;
	size_t generationsPassed = 0;

public:
	auto TrainUnsupervised(SpeciesManager::Bodies& bodies) -> Trained::NeuralNetwork;
	template <typename Classification, std::size_t ClassificationCount>
	auto TrainSupervised(const Data<Classification, ClassificationCount>& data, std::size_t trainingInstances = 200) -> Trained::Classifier<Classification>;
	
	auto GetGenerationsPassed() const { return generationsPassed; }

	friend std::ostream& operator<<(std::ostream& stream, const NeuralNetworkTrainer & neuralNetworkTrainer);


private:
	auto TrainGenerationAndLogUsingBodies(SpeciesManager::Bodies& bodies) -> void;
	auto UpdateEntireGeneration() -> void;
};

template <typename Classification, std::size_t ClassificationCount>
auto NeuralNetworkTrainer::TrainSupervised(const Data<Classification, ClassificationCount>& data, std::size_t trainingInstances) -> Trained::Classifier<Classification> {
	using supervised_body_t = Body::SupervisedLearning<Classification, ClassificationCount>;
	std::vector<supervised_body_t> bodies(trainingInstances, supervised_body_t {data});
	SpeciesManager::Bodies bodyRefs(bodies.begin(), bodies.end());
	auto champ = TrainUnsupervised(bodyRefs);
	return Trained::Classifier<Classification>(std::move(champ));
}

}
