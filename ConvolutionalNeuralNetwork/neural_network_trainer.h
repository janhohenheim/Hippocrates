#pragma once
#include "training_data.h"
#include "multi_matrix.h"
#include "multi_matrix_factory.h"
#include "neuron.h"

namespace Convolutional {

template <typename TrainingData>
class NeuralNetworktrainer {
public:
	explicit NeuralNetworktrainer(const std::vector<TrainingData>& trainingData):
		trainingData(trainingData){};

	auto Train() {
		for (const auto& currTrainigSet : trainingData) {
			auto multiMatrix = MultiMatrixFactory::GetMultiMatrix(currTrainigSet.data);
			auto features = SubSampler::Neuron(1, { 1,1,1,1,1,1,1,1,1 }).ProcessMultiMatrix(multiMatrix);
			// auto pooledFeatures = SubSampler::MaxPooler(1, { 1,1,1,1,1,1,1,1,1 }).ProcessMultiMatrix(features);
		}
		return MultiMatrix({});
	}

private:
	const std::vector<TrainingData>& trainingData;
};

}
