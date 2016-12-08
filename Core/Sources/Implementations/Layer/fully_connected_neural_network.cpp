#include "Layer/fully_connected_neural_network.hpp"

using namespace Convolutional::Layer;

FullyConnectedNeuralNetwork::FullyConnectedNeuralNetwork(std::size_t outputCount) {
	// No hidden layers because this class represents a single layer
}
	
auto FullyConnectedNeuralNetwork::ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix {
	const auto inputCount = multiMatrix.GetDimensionCount();

	// Getting the inputs
	for (const auto& subMatrix : multiMatrix) {
		for (auto input : subMatrix) {

		}
	}

}
