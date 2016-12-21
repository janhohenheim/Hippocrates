#pragma once
#include "neural_network.hpp"
#include "Layer/Pooler/max_pooler.hpp"
#include "training_data.hpp"
#include "Utility/fillable_ref.hpp"
#include "Learning/backpropagation.hpp"

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
			NeuralNetwork<Classification> net{this->layers};
			neuralNetworks.push_back(std::move(net));
		}
	}
	NeuralNetworktrainer(const NeuralNetworktrainer&) = default;
	NeuralNetworktrainer(NeuralNetworktrainer&&) = default;

	auto Train() {
		std::unique_ptr<Learning::ILearningMethod<Classification>> learningMethod = 
			std::make_unique<Learning::Backpropagation<Classification>>(neuralNetworks, trainingData);

		while (!learningMethod->IsFinished())
			for (auto network = neuralNetworks.begin(); network != neuralNetworks.end(); ++network) {
				learningMethod->BeginEpoch(network);
				for (auto set = trainingData.begin(); set != trainingData.end(); ++set) {
					learningMethod->EvaluateSet(network, set);
				}
				learningMethod->EndEpoch(network);
			}

		return learningMethod->GetChamp();
	}

private:
	TrainigDataType trainingData;
	Layer::Layers layers;
	std::vector<NeuralNetwork<Classification>> neuralNetworks;
};

}
