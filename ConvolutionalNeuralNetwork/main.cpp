//
// Created by jnf on 07.09.16.
//
#include "neural_network_trainer.h"
#include "multi_matrix.h"
#include "multi_matrix_factory.h"
#include "sentence.h"

#include <string>

using namespace Convolutional;

enum class Categories {
	Even,
	Uneven,

	CategoryCount
};

using trainingDataType = TrainingData<InputData::Sentence, Categories>::CategorizedData;

auto GetTrainigData() {
	std::vector<trainingDataType> dataVector;
	for (std::size_t i = 0; i < 100; ++i){
		InputData::Sentence trainigSentence(std::to_string(i));
		trainingDataType data{trainigSentence};
		data.classification = static_cast<Categories>(i % 2);

		dataVector.push_back(std::move(data));
	}
	return dataVector;
}

int main() {
	auto trainingData(GetTrainigData());
	NeuralNetworktrainer<trainingDataType> networktrainer{trainingData};

	auto trainedNetwork = networktrainer.Train();
	return 0;
}
