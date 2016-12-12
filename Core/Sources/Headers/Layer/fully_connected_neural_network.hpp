#pragma once
#include "ilayer.hpp"
#include <stdlib.h>

namespace Convolutional::Layer {

class FullyConnectedNeuralNetwork : public ILayer {
public:	
	using ILayer::ILayer;

	class Neuron;

	class Connection {
	public:
		Neuron& from;
		Neuron& to;

		double weight = ((double) rand() / RAND_MAX * 2) - 1;

		Connection(Neuron& from, Neuron& to) : from(from), to(to) { };
	};

	class Neuron {
	public:
		Matrix::element_t lastActionPotential = 0;
		std::vector<Connection> connections;

		Neuron(std::size_t nConnections = 0) { connections.reserve(nConnections); };

		auto AddConnection(Connection& connection) -> void {
			connections.push_back(connection);
		}
	};

	class BiasNeuron: public Neuron {
	public:
		BiasNeuron() { lastActionPotential = 1.0; };
	};

	std::size_t nOutputs;
	std::vector<Neuron> inputNeurons;
	std::vector<Neuron> outputNeurons;

	FullyConnectedNeuralNetwork(std::size_t outputCount): nOutputs(outputCount), outputNeurons(outputCount, Neuron()) { };
	FullyConnectedNeuralNetwork(const FullyConnectedNeuralNetwork&) = default;
	FullyConnectedNeuralNetwork(FullyConnectedNeuralNetwork&&) = default;

	auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix override;
	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return {0, 0}; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<FullyConnectedNeuralNetwork>(*this); }
};

}
