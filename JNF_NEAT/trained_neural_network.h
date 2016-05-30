#pragma once
#include "neural_network.h"
#include <string>

class TrainedNeuralNetwork {
	public:
		TrainedNeuralNetwork() = delete;
		explicit TrainedNeuralNetwork(const NeuralNetwork& network);
		explicit TrainedNeuralNetwork(NeuralNetwork&& network);
		explicit TrainedNeuralNetwork(const NeuralNetwork&& network) = delete;
		TrainedNeuralNetwork(const TrainedNeuralNetwork& other) = default;
		~TrainedNeuralNetwork() = default;

		TrainedNeuralNetwork& operator=(const TrainedNeuralNetwork& other) = default;

		static TrainedNeuralNetwork LoadFromFile(const std::string& fileName);
		void SaveToFile(const std::string& fileName) const;

		std::vector<float> GetOutputs(const std::vector<float>& inputs);

	private:
		NeuralNetwork trainedNetwork;
};