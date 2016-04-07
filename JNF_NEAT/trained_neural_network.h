#pragma once
#include "neural_network.h"
#include <string>

class TrainedNeuralNetwork {
	public:
		TrainedNeuralNetwork() = default;
		explicit TrainedNeuralNetwork(const NeuralNetwork & trainedNetwork);
		TrainedNeuralNetwork(const TrainedNeuralNetwork & other) = default;
		~TrainedNeuralNetwork() = default;

		void LoadFromFile(const std::string & fileName);
		void SaveToFile(const std::string & fileName) const;

		std::vector<float> GetOutputs(const std::vector<float> & inputs);

	private:
		NeuralNetwork trainedNetwork;
};