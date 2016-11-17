#pragma once

#include <chrono>
#include <future>
#include <memory>

// TODO: Replace with library import
#include "../../../../Core/Sources/Headers/training/neural_network_trainer.hpp"

namespace Hippocrates::Tests::TestingUtilities {

template <typename Classification, typename Rep, typename Period>
auto TrainWithTimeout(Training::NeuralNetworkTrainer& trainer, const Training::Data<Classification> &data, std::chrono::duration<Rep, Period> span) {
	using classifier_t = Trained::Classifier<Classification>;
	auto func = [&]() {
		auto champ = trainer.TrainSupervised(data, static_cast<std::size_t>(150));
		return std::make_unique<classifier_t>(std::move(champ));
	};
	std::future<std::unique_ptr<classifier_t>> fut = std::async(std::launch::async, func);

	if (fut.wait_for(span) == std::future_status::timeout) {
		std::terminate();
	}

	return *(fut.get().get());
}


template <typename Classification>
auto TestNetwork(Trained::Classifier<Classification> & network, Training::Data<Classification> &data) {
	for (const auto& dataSet : data) {
		if (network.Classify(dataSet.input) != dataSet.classification) {
			return 1;
		}
	}
	return 0;
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
