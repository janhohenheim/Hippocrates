#pragma once
#include "neural_network.hpp"
#include <fstream>

namespace Hippocrates {

class TrainedNeuralNetwork : public NeuralNetwork {
public:
	using NeuralNetwork::NeuralNetwork;
	static auto LoadFromFile(const std::ifstream& fileName) -> TrainedNeuralNetwork;
	auto SaveToFile(std::ofstream& file) const -> void;

private:

	static auto LoadGenomeFromFile(const std::ifstream& file) -> Genome;
	static auto LoadTrainigParametersFromFile(const std::ifstream& file) -> TrainingParameters;
};

}
