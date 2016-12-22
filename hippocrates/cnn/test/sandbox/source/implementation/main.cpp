#include "neural_network_trainer.hpp"
#include "input_data/sentence.hpp"
#include "Learning/learning_method.hpp"
#include "input_data/image.hpp"
#include "layer/fully_connected_neural_network.hpp"
#include "layer/filters.hpp"

using namespace Convolutional;

enum class Categories {
	Cat,
	NotCat,

	CategoryCount
};

int main() {
	TrainingData<Categories> trainingData;
	InputData::Image someCat("../../image.png");
	trainingData.AddData(std::move(someCat), Categories::Cat);

	Layer::Layers layers {
		Layer::Filters{3},
		Layer::ReLU{},
		Layer::Pooler::MaxPooler{},
		Layer::FullyConnectedNeuralNetwork{static_cast<std::size_t>(Categories::CategoryCount)}
	};

	NeuralNetworktrainer<Categories> networktrainer {
		50,
		std::move(trainingData),
		std::move(layers)
	};

	auto trainedNetwork = networktrainer.Train();
	return 0;
}
