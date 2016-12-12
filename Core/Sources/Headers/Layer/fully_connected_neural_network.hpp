#pragma once
#include "ilayer.hpp"
#include "Utility/utility.hpp"
#include <stdlib.h>

namespace Convolutional::Layer {

class FullyConnectedNeuralNetwork : public ILayer {
public:	
	using ILayer::ILayer;

	struct Neuron;
	struct Connection {
		Connection(Neuron& from, Neuron& to) : from(from), to(to) { };

		Neuron& from;
		Neuron& to;
		double weight = Utility::GetRandomNumberBetween(-1.0, 1.0);
	};

	struct Neuron {
		Matrix::element_t lastActionPotential = 0;
		std::vector<Connection> connections;

		Neuron() = default;
		Neuron(std::size_t nConnections) { connections.reserve(nConnections); };
	};

	struct BiasNeuron: public Neuron {
		BiasNeuron() { lastActionPotential = 1.0; };
	};

	std::vector<Neuron> inputNeurons;
	std::vector<Neuron> outputNeurons;

	FullyConnectedNeuralNetwork(std::size_t outputCount) : outputNeurons {outputCount, Neuron {}} { };
	FullyConnectedNeuralNetwork(const FullyConnectedNeuralNetwork&) = default;
	FullyConnectedNeuralNetwork(FullyConnectedNeuralNetwork&&) = default;

	auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix override;
	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return {0, 0}; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<FullyConnectedNeuralNetwork>(*this); }
};

}
