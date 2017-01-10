#include "neural_network_trainer.hpp"
#include "input_data/image.hpp"
#include "layer/all_layers.hpp"

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

	auto FirstPoolingRes = [](std::size_t convSize) {
		const auto conv = Layer::Convolution{convSize, Layer::Filter {{3, 3}, {1, 1}, {1, 1}}};
		const auto scaler = Layer::DimensionScaler {convSize};
		const auto factor = std::size_t {4};
		return Layer::ResidualBlock::Pooling::Bottlenecked {conv, scaler, factor};
	};

	auto PoolingRes = [](std::size_t convSize) {
		const auto conv = Layer::Convolution {convSize, Layer::Filter {{3, 3}, {1, 1}, {1, 1}}};
		const auto scaler = Layer::DimensionScaler {convSize, {2, 2}};
		const auto factor = std::size_t {4};
		return Layer::ResidualBlock::Pooling::Bottlenecked {conv, scaler, factor}; 
	};

	auto IdentityRes = [](std::size_t convSize) {
		return Layer::ResidualBlock::IdentityMapping::Bottlenecked {Layer::Convolution {convSize, Layer::Filter {{3, 3}, {1, 1}, {1, 1}}}};
	};

	// ResNet 50 v2
	Layer::Layers layers {
		Layer::Convolution {64, Layer::Filter {{7, 7}, {2, 2}, {3, 3}}},
		Layer::ReLU {},
		Layer::Pooler::MaxPooler {{3, 3}, {2, 2}},

		FirstPoolingRes(64),
		IdentityRes(64),
		IdentityRes(64),

		PoolingRes(128),
		IdentityRes(128),
		IdentityRes(128),
		IdentityRes(128),

		PoolingRes(256),
		IdentityRes(256),
		IdentityRes(256),
		IdentityRes(256),

		PoolingRes(512),
		IdentityRes(512),
		IdentityRes(512),
		IdentityRes(256),
		IdentityRes(256),
		IdentityRes(256),
		
		Layer::ReLU{},
		Layer::Pooler::GlobalAveragePooler{},
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
