#include "fully_connected_neural_network.hpp"

namespace Convolutional::Layer {

	FullyConnectedNeuralNetwork(std::size_t inputCount,
								std::size_t outputCount,
								std::size_t hiddenLayerCount,
								std::size_t hiddenLayerSize)
    {}
	
	auto FullyConnectedNeuralNetwork::ProcessMatrix(Matrix::Position position, const Matrix& net) const -> Matrix override {}
	auto FullyConnectedNeuralNetwork::GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override {}
	auto FullyConnectedNeuralNetwork::GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override {}
	auto FullyConnectedNeuralNetwork::GetStride(Matrix::Size size) const noexcept -> Matrix::Size override {}
}
