#pragma once
#include "training_data.h"
#include "multi_dimensional_matrix.h"

namespace Convolutional {

template <typename Category>
class NeuralNetworktrainer {
public:
    NeuralNetworktrainer(const TrainingData<MultiDimensionalMatrix, Category>& trainingData): 
        trainingData(trainingData){};
    auto Train() -> MultiDimensionalMatrix;

private:
    const TrainingData<MultiDimensionalMatrix, Category>& trainingData;
};

}