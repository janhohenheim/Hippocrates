#pragma once

// TODO: Replace with library import
#include "../../../../Core/Sources/Headers/neural_network_trainer.h"
#include <iostream>

namespace Hippocrates {
namespace Tests {
namespace TestingUtilities {

template <typename InputType, typename Classification>
auto TestNetwork(NeuralNetwork &network, TrainingData<InputType, Classification> &data) {
	auto errorCount = 0;

	for (const auto& dataSet : data) {
		auto networkOutputs = network.GetOutputsUsingInputs(dataSet.input);

		auto maxOutput = std::max_element(networkOutputs.begin(), networkOutputs.end());
		auto outputIndex = std::distance(networkOutputs.begin(), maxOutput);

		if (outputIndex != static_cast<size_t>(dataSet.classification)) {
			std::cout << "Incorrect classification for inputs:";
			for (const auto& input : dataSet.input) {
				std::cout << " - " << input << '\n';
			}

			std::cout << "Got outputs:";
			for (const auto& output : networkOutputs) {
				std::cout << " - " << output << '\n';
			}

			std::cout << '\n';
		}
	}

	return errorCount;
}

}
}
}
