#pragma once
#include "neural_network.h"
#include <string>

namespace JNF_NEAT {

	class TrainedNeuralNetwork : public NeuralNetwork {
		public:
			using NeuralNetwork::NeuralNetwork;
			static TrainedNeuralNetwork LoadFromFile(const std::string& fileName);
			void SaveToFile(const std::string& fileName) const;
	};

}