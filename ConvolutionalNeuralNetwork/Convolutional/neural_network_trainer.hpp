#pragma once
#include "neural_network.hpp"
#include "Layer/Pooler/max_pooler.hpp"
#include "training_data.hpp"

namespace Convolutional {

template <typename Classification>

class NeuralNetworktrainer {
	using TrainigDataType = TrainingData<Classification>;

public:
	explicit NeuralNetworktrainer(
		std::size_t networkCount, 
		const TrainigDataType& trainingData, 
		Layer::Layers&& layers) :

		trainingData(trainingData),
		layers{std::move(layers)}
	{
		GenerateNetworks(networkCount);
	}

	explicit NeuralNetworktrainer(
		std::size_t networkCount,
		TrainigDataType&& trainingData,
		Layer::Layers&& layers) :

		TrainingDataAsValue{ std::move(trainingData) },
		trainingData{ TrainingDataAsValue },
		layers{ std::move(layers) }
	{
		GenerateNetworks(networkCount);
	}

	auto Train() {
		for (const auto& set : trainingData) {

		}
		return neuralNetworks.front();
	}

private:
	auto GenerateNetworks(std::size_t networkCount) {
		neuralNetworks.reserve(networkCount);
		for (std::size_t i = 0; i < networkCount; ++i) {
			neuralNetworks.emplace_back(this->layers);
		}
	}

private:
	[[maybe_unused]] TrainigDataType TrainingDataAsValue;
	const TrainigDataType& trainingData;
	Layer::Layers layers;
	std::vector<NeuralNetwork<Classification>> neuralNetworks;
};

}
