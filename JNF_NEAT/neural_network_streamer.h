#pragma once
#include <string>
#include "neural_network.h"

class NeuralNetworkStreamer {
public:
	static std::string GetString(const NeuralNetwork& net);
};