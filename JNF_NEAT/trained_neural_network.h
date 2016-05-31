#pragma once
#include "neural_network.h"
#include <string>

class TrainedNeuralNetwork : public NeuralNetwork {
	public:
		NeuralNetwork::NeuralNetwork;
		static TrainedNeuralNetwork LoadFromFile(const std::string& fileName);
		void SaveToFile(const std::string& fileName) const;

		std::string GetGenomeAsString() const;
};