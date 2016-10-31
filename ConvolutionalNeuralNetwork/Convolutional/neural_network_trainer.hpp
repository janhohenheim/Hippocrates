#pragma once
#include "neural_network.hpp"
#include "Layer/Pooler/max_pooler.hpp"
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
			NeuralNetwork<Classification> net(Layer::Filter(1.0, {1.0}), Layer::Pooler::MaxPooler());
			auto result = net.ClassifyMultiMatrix(set.multiMatrix);
			if (result == set.classification) {
				// Good
			}
			else {
				// Bad
			}
		}
		return NeuralNetwork<Classification> (Layer::Filter(1.0, {1.0}), Layer::Pooler::MaxPooler());
	}

private:
	const TrainigDataType trainingData;
};

}
