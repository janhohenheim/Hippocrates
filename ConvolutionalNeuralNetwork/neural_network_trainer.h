#pragma once
#include "training_data.h"
#include "multi_matrix.h"

namespace Convolutional {

template <typename Category>
class NeuralNetworktrainer {
public:
    using Data = TrainingData<MultiMatrix, Category>;
    NeuralNetworktrainer(const std::vector<Data>& trainingData):
        trainingData(trainingData){};

    auto Train() {
        return MultiMatrix({});
    }

private:
    const std::vector<Data>& trainingData;
};

}
