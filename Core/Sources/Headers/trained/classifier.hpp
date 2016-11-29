#pragma once
#include <algorithm>
#include "neural_network.hpp"

namespace Hippocrates::Trained {

template<typename Classification>
class Classifier : public NeuralNetwork {
public:
	using NeuralNetwork::NeuralNetwork;
	Classifier() : NeuralNetwork(){ };
	Classifier(const NeuralNetwork& other) : NeuralNetwork(other){};
	Classifier(NeuralNetwork&& other) : NeuralNetwork(std::move(other)){};

	auto Classify(const Type::neuron_values_t& inputs) {
		const auto outputs = GetOutputsUsingInputs(inputs);
		const auto maxOutput = std::max_element(outputs.begin(), outputs.end());
		const auto outputIndex = std::distance(outputs.begin(), maxOutput);
		return static_cast<Classification>(outputIndex);
	}
};

}
