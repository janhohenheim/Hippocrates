#pragma once
#include "trained_neural_network.hpp"

namespace Hippocrates {
namespace Trained {

template<typename Classification>
class Classifier : public TrainedNeuralNetwork {
public:
	using TrainedNeuralNetwork::TrainedNeuralNetwork;
	Classifier() : TrainedNeuralNetwork(){ };
	Classifier(const TrainedNeuralNetwork& other) : TrainedNeuralNetwork(other){};
	Classifier(TrainedNeuralNetwork&& other) : TrainedNeuralNetwork(std::move(other)){};

	auto Classify(const Type::neuron_values_t& inputs) {
		auto outputs = GetOutputsUsingInputs(inputs);
		auto maxOutput = std::max_element(outputs.begin(), outputs.end());
		auto outputIndex = std::distance(outputs.begin(), maxOutput);
		return static_cast<Classification>(outputIndex);
	}
};

}
}