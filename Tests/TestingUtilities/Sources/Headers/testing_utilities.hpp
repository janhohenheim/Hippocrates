#pragma once

// TODO: Replace with library import
#include "../../../../Core/Sources/Headers/neural_network_trainer.hpp"
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

template<typename TimeT = std::chrono::milliseconds>
struct measure {
	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
			(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};

}
}
}
