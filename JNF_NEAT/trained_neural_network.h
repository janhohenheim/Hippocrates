#pragma once
#include "neural_network.h"
#include <string>

class TrainedNeuralNetwork {
	public:
		TrainedNeuralNetwork() = default;
		explicit TrainedNeuralNetwork(const NeuralNetwork & trainedNetwork);
		TrainedNeuralNetwork(const TrainedNeuralNetwork & other) = default;
		~TrainedNeuralNetwork() = default;

		void LoadFromFile(std::string fileName);
		void SaveToFile(std::string fileName) const;

		// TODO jnf
		// Think about how the User can elegantly use the trained network

	private:
		NeuralNetwork trainedNetwork;
};