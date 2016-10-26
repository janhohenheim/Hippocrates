#pragma once
#include "neural_network.hpp"
#include "SubSampler/Pooler/max_pooler.hpp"
#include "training_data.hpp"

namespace Convolutional {

template <typename Classification>

class NeuralNetworktrainer {
	using TrainigDataType = TrainingData<Classification>;

public:
	explicit NeuralNetworktrainer(TrainigDataType trainingData) :
		trainingData(std::move(trainingData))
	{}

	auto Train() {
		for (const auto& set : trainingData) {
			NeuralNetwork<SubSampler::Pooler::MaxPooler, Classification> net;
			auto result = net.ClassifyMultiMatrix(set.multiMatrix);
			if (result == set.classification) {
				// Good
			}
			else {
				// Bad
			}
		}
		return NeuralNetwork<SubSampler::Pooler::MaxPooler, Classification>();
	}

private:
	const TrainigDataType trainingData;
};

}
