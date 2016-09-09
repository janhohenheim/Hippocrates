#pragma once
#include "neural_network.h"
#include <fstream>

namespace JNF_NEAT {

class TrainedNeuralNetwork : public NeuralNetwork {
public:
	using NeuralNetwork::NeuralNetwork;
	static auto LoadFromFile(const std::ifstream& fileName) -> TrainedNeuralNetwork;
	auto SaveToFile(std::ofstream& file) const -> void;
};

}
