#include "neural_network_trainer.hpp"
#include "input_data/image.hpp"

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
		Layer::Convolution{3},
		Layer::ReLU{},
		Layer::Pooler::MaxPooler{},
		Layer::FullyConnected{static_cast<std::size_t>(Categories::CategoryCount)}
	};

	NeuralNetworktrainer<Categories> networktrainer {
		50,
		std::move(trainingData),
		std::move(layers)
	};

	auto trainedNetwork = networktrainer.Train();
	return 0;
}
