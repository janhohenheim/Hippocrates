#include "neural_network_trainer.hpp"
#include "sentence.hpp"
#include "learning_method.hpp"

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
	Layer::Layers layers {
		Layer::Filter{ 1.0, { 1.0 } },
		Layer::Pooler::MaxPooler{}
	};

	NeuralNetworktrainer<Categories> networktrainer{
		50,
		std::move(trainingData),
		std::move(layers)
	};

	auto trainedNetwork = networktrainer.Train();

	//Learning::memes<Categories> m(trainedNetwork, trainingData);
	return 0;
}
