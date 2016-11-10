#pragma once

// TODO: Replace with library import
#include "../../../../Core/Sources/Headers/neural_network_trainer.hpp"
#include <iostream>
#include <chrono>
#include <future>
#include <memory>
#include <sstream>
#include <thread>
#ifdef __has_include
#  if __has_include(<pthread.h>)
#    include <pthread.h>
#  endif
#endif

namespace Hippocrates {
namespace Tests {
namespace TestingUtilities {

template <typename InputType, typename Classification, typename Rep, typename Period>
auto TrainWithTimeout(NeuralNetworkTrainer& trainer, const TrainingData<InputType, Classification> &data, std::chrono::duration<Rep, Period> span) {
	auto func = [&]() {
		auto champ = trainer.TrainSupervised(data, static_cast<std::size_t>(150));
		return std::make_unique<TrainedNeuralNetwork>(std::move(champ));
	};
	std::future<std::unique_ptr<TrainedNeuralNetwork>> fut = std::async(std::launch::async, func);

	if (fut.wait_for(span) == std::future_status::timeout) {
		std::terminate();
	}

	return *(fut.get().get());
}


template <typename InputType, typename Classification>
auto TestNetwork(NeuralNetwork &network, TrainingData<InputType, Classification> &data) {
	auto errorCount = 0;

	for (const auto& dataSet : data) {
		auto networkOutputs = network.GetOutputsUsingInputs(dataSet.input);

		auto maxOutput = std::max_element(networkOutputs.begin(), networkOutputs.end());
		auto outputIndex = std::distance(networkOutputs.begin(), maxOutput);

		if (outputIndex != static_cast<size_t>(dataSet.classification)) {
			errorCount++;
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
