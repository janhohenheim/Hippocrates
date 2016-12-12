#include "Layer/fully_connected_neural_network.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto FullyConnectedNeuralNetwork::ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix {
	const auto inputCount = multiMatrix.GetDimensionCount() * multiMatrix.GetElementCount();

	inputNeurons = std::vector<Neuron>(inputCount, Neuron());
	inputNeurons.push_back(BiasNeuron());

	outputNeurons = std::vector<Neuron>(outputNeurons.size(), Neuron(inputCount + 1));

	for (auto& input : inputNeurons)
		for (auto& output : outputNeurons)
			output.AddConnection({input, output});

	for (auto& input : inputNeurons)
		for (const auto& subMatrix : multiMatrix)
			for (const auto& element : subMatrix)
				input.lastActionPotential = element;

	for (auto& neuron : outputNeurons) {
		for (const auto& connection : neuron.connections) {
			neuron.lastActionPotential += connection.from.lastActionPotential * connection.weight;
		}
		neuron.lastActionPotential = tanh(neuron.lastActionPotential);
	}

	Matrix::Size size;
	size.width = outputNeurons.size();
	size.height = 1;

	Matrix outputs(std::move(size));

	for (std::size_t i = 0; i < outputNeurons.size(); i++) {
		outputs.ElementAt({i, 0}) = outputNeurons[i].lastActionPotential;
	}

	return MultiMatrix {{outputs}};
}
