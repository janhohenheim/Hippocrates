#include "layer/fully_connected_neural_network.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto FullyConnected::ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix {
	BuildNetwork(multiMatrix.GetDimensionCount() * multiMatrix.GetElementCount());
	LoadInputs(multiMatrix);
	ProcessOutputs();
	const auto outputs = GetOutputsAsMatrix();
	return MultiMatrix {{outputs}};
}

auto FullyConnected::BuildNetwork(std::size_t inputCount) -> void {
	if (wasBuilt)
		return;

	inputNeurons = std::vector<Neuron>(inputCount, Neuron{});
	inputNeurons.push_back(BiasNeuron {});

	outputNeurons = std::vector<Neuron> {outputNeurons.size(), Neuron {inputCount + 1}};

	for (auto& input : inputNeurons)
		for (auto& output : outputNeurons)
			output.connections.push_back({input, output});

	wasBuilt = true;
}

auto FullyConnected::LoadInputs(const MultiMatrix & multiMatrix) -> void {
	auto input = inputNeurons.begin();
	for (const auto& subMatrix : multiMatrix)
		for (const auto& element : subMatrix)
			(input++)->lastActionPotential = element;
}

auto FullyConnected::ProcessOutputs() -> void {
	for (auto& neuron : outputNeurons) {
		for (const auto& connection : neuron.connections) {
			neuron.lastActionPotential += connection.from.lastActionPotential * connection.weight;
		}
		neuron.lastActionPotential = tanh(neuron.lastActionPotential);
	}
}

auto FullyConnected::GetOutputsAsMatrix() const -> Matrix {
	Matrix::Size size;
	size.width = outputNeurons.size();
	size.height = 1;

	Matrix outputs(std::move(size));

	for (std::size_t i = 0; i < outputNeurons.size(); i++)
		outputs.ElementAt({i, 0}) = outputNeurons[i].lastActionPotential;

	return outputs;
}
