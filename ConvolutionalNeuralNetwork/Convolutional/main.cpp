#include "neural_network_trainer.hpp"
#include "InputData/sentence.hpp"

using namespace Convolutional;

enum class Categories {
	Even,
	Uneven,

	CategoryCount
};

auto GetTrainigData() {
	TrainingData<Categories> trainingData;
	for (std::size_t i = 0; i < 100; ++i) {
		InputData::Sentence trainigSentence = std::to_string(i);
		Categories classification = static_cast<Categories>(i % 2);

		trainingData.AddData(std::move(trainigSentence), classification);
	}
	return trainingData;
}

int main() {
	auto trainingData(GetTrainigData());
	NeuralNetworktrainer<Categories> networktrainer{std::move(trainingData)};

	auto trainedNetwork = networktrainer.Train();
	return 0;
}
