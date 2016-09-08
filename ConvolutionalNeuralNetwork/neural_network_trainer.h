#pragma once
#include "training_data.h"
#include "multi_dimensional_matrix.h"

namespace Convolutional {

template <typename Category>
class NeuralNetworktrainer {
public:
    using Data = TrainingData<MultiDimensionalMatrix, Category>;
    NeuralNetworktrainer(const std::vector<Data>& trainingData):
        trainingData(trainingData){};

    auto Train() {
        return MultiDimensionalMatrix({});
    }

private:
    const std::vector<Data>& trainingData;
};

}
