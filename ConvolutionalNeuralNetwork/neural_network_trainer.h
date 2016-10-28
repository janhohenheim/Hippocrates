#pragma once
#include "neural_network.h"
#include "max_pooler.h"
#include "training_data.h"

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
			NeuralNetwork<Classification> net(SubSampler::Neuron(1.0, {1.0}), SubSampler::Pooler::MaxPooler());
			auto result = net.ClassifyMultiMatrix(set.multiMatrix);
			if (result == set.classification) {
				// Good
			}
			else {
				// Bad
			}
		}
		return NeuralNetwork<Classification> (SubSampler::Neuron(1.0, {1.0}), SubSampler::Pooler::MaxPooler());
	}

private:
	const TrainigDataType trainingData;
};

}
