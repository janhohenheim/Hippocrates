#include "neural_network_trainer.hpp"
#include "InputData/sentence.hpp"
#include "Learning/learning_method.hpp"
#include "InputData/image.hpp"
#include "Layer/fully_connected_neural_network.hpp"
#include "Layer/filters.hpp"

using namespace Convolutional;

enum class Categories {
	Cat,
	NotCat,

	CategoryCount
};

int main(int argc, char* argv[]){
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
