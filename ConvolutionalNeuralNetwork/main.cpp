//
// Created by jnf on 07.09.16.
//
#include "neural_network_trainer.h"

using namespace Convolutional;

enum class Categories {
    Even,
    Uneven,

    CategoryCount
};

using trainingDataType = TrainingData::CategorizedData<int, Categories>;

auto GetTrainigData() {
    std::vector<trainingDataType> dataVector;
    for (std::size_t i = 0; i < 100; ++i){
        trainingDataType data;
        data.data = i;
        data.classification = static_cast<Categories>(i % 2);

        dataVector.push_back(std::move(data));
    }
}

int main() {
    auto trainingData(GetTrainigData());
    NeuralNetworktrainer networktrainer(std::move(trainingData));

    auto trainedNetwork = networktrainer.Train();
    return 0;
}