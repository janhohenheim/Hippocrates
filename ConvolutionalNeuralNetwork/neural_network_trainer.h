#pragma once
#include "training_data.h"
#include "multi_matrix.h"

namespace Convolutional {

template <typename TrainingData>
class NeuralNetworktrainer {
public:
	explicit NeuralNetworktrainer(const std::vector<TrainingData>& trainingData):
		trainingData(trainingData){};

	auto Train() {
		for (const auto& currTrainigSet : trainingData) {
			auto currInput = MultiMatrixFactory::GetMultiMatrix(currTrainigSet.data);
		}
		return MultiMatrix({});
	}

private:
	const std::vector<TrainingData>& trainingData;
};

}
