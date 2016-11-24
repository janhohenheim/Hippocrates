#pragma once
#include "neural_network.hpp"
#include "max_pooler.hpp"
#include "training_data.hpp"
#include "fillable_ref.hpp"
#include "learning_method.hpp"
#include "backpropagation.hpp"

namespace Convolutional {

template <typename Classification>

class NeuralNetworktrainer {
	using TrainigDataType = TrainingData<Classification>;

public:
	explicit NeuralNetworktrainer(
		std::size_t networkCount, 
		TrainigDataType trainingData, 
		Layer::Layers layers) :

		trainingData{ std::move(trainingData) },
		layers{ std::move(layers) }
	{
		neuralNetworks.reserve(networkCount);
		for (std::size_t i = 0; i < networkCount; ++i) {
			neuralNetworks.emplace_back(layers);
		}
	}

	auto Train() {
		std::unique_ptr<Learning::ILearningMethod<Classification>> learningMethod = 
			std::make_unique<Learning::Backpropagation<Classification>>(neuralNetworks, trainingData.Get());
		for (auto network = neuralNetworks.begin(); network != neuralNetworks.end(); ++network) {
			learningMethod->BeginEpoch(network);
			for (auto set = trainingData.Get().begin(); set != trainingData.Get().end(); ++set) {
				learningMethod->EvaluateSet(network, set);
			}
			learningMethod->EndEpoch(network);
		}

		// Todo jnf:
		// Return fittest
		return neuralNetworks.front();
	}

private:
	const Hippocrates::Utility::FillableRef<TrainigDataType> trainingData;
	Hippocrates::Utility::FillableRef<Layer::Layers> layers;
	std::vector<NeuralNetwork<Classification>> neuralNetworks;
};

}
