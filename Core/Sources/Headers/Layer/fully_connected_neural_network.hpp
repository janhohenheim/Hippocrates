#pragma once
#include "ilayer.hpp"

namespace Convolutional::Layer {

class FullyConnectedNeuralNetwork : public ILayer {
public:	
	FullyConnectedNeuralNetwork(std::size_t inputCount,
								std::size_t outputCount,
								std::size_t hiddenLayerCount = 1,
								std::size_t hiddenLayerSize = 6);
	
	auto ProcessMatrix(Matrix net) const -> Matrix override;
	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return {0, 0}; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<FullyConnectedNeuralNetwork>(*this); }
};

}
