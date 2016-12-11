#include "Layer/fully_connected_neural_network.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto FullyConnectedNeuralNetwork::ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix {
	const auto inputCount = multiMatrix.GetDimensionCount() * multiMatrix.GetElementCount();

	inputNeurons = std::vector<Neuron>(inputCount, Neuron(nOutputs));
	inputNeurons.push_back(BiasNeuron(nOutputs));

	for (std::size_t i = 0; i < multiMatrix.GetDimensionCount(); i++) {
		for (std::size_t j = 0; j < multiMatrix.GetElementCount(); j++) {
			for (std::size_t k = 0; k < nOutputs; k++) {
				Connection connection(inputNeurons[i * multiMatrix.GetElementCount() + j], outputNeurons[i]);
				inputNeurons[i * multiMatrix.GetElementCount() + j].AddConnection(connection);
			}
		}
	}

	std::size_t currentNeuron = 0;
	for (const auto& subMatrix : multiMatrix) {
		for (auto input : subMatrix) {
			inputNeurons[currentNeuron].lastActionPotenzial = input;
			inputNeurons[currentNeuron].Fire();

			currentNeuron++;
		}
	}

	std::vector<double> outputs(nOutputs);
	for (auto neuron : outputNeurons) {
		outputs.push_back(tanh(neuron.lastActionPotenzial));
	}

	return MultiMatrix {{outputs}};
}

auto FullyConnectedNeuralNetwork::Neuron::Fire() -> void {
	for (auto connection : connections) {
		connection.to.lastActionPotenzial += tanh(lastActionPotenzial) * connection.weight;
	}
}
