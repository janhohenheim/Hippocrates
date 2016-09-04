#pragma once
#include "neural_network.h"
#include <string>

namespace JNF_NEAT {

class TrainedNeuralNetwork : public NeuralNetwork {
public:
	using NeuralNetwork::NeuralNetwork;
	static auto LoadFromFile(const std::string& fileName)->TrainedNeuralNetwork;
	auto SaveToFile(const std::string& fileName) const -> void;
};

}
