//
// Created by jnf on 07.09.16.
//
#include "neural_network_trainer.h"
#include "multi_dimensional_matrix.h"

using namespace Convolutional;

enum class Categories {
    Even,
    Uneven,

    CategoryCount
};

using trainingDataType = TrainingData<MultiDimensionalMatrix, Categories>::CategorizedData;

auto GetTrainigData() {
    std::vector<trainingDataType> dataVector;
    for (std::size_t i = 0; i < 100; ++i){
        trainingDataType data {MultiDimensionalMatrix({})};
        data.classification = static_cast<Categories>(i % 2);

        dataVector.push_back(std::move(data));
    }
    return dataVector;
}

int main() {
    auto trainingData(GetTrainigData());
    NeuralNetworktrainer<Categories> networktrainer({trainingData});

    auto trainedNetwork = networktrainer.Train();
    return 0;
}