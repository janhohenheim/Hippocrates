#include "Layer/fully_connected_neural_network.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto FullyConnectedNeuralNetwork::ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix {
	const auto inputCount = multiMatrix.GetDimensionCount() * multiMatrix.GetElementCount();

	inputNeurons = std::vector<Neuron>(inputCount, Neuron());
	inputNeurons.push_back(BiasNeuron());

	outputNeurons = std::vector<Neuron>(nOutputs, Neuron(inputCount + 1));

	for (std::size_t i = 0; i < multiMatrix.GetDimensionCount(); i++) {
		for (std::size_t j = 0; j < multiMatrix.GetElementCount(); j++) {
			for (std::size_t k = 0; k < nOutputs; k++) {
				Connection connection(inputNeurons[i * multiMatrix.GetElementCount() + j], outputNeurons[i]);
				outputNeurons[i].AddConnection(connection);
			}
		}
	}

	std::size_t currentNeuron = 0;
	for (const auto& subMatrix : multiMatrix) {
		for (auto input : subMatrix) {
			inputNeurons[currentNeuron].lastActionPotenzial = input;
			currentNeuron++;
		}
	}

	for (auto neuron : outputNeurons) {
		for (auto connection : neuron.connections) {
			neuron.lastActionPotenzial += connection.from.lastActionPotenzial * connection.weight;
		}
	}

	std::vector<double> outputs(nOutputs);
	for (auto neuron : outputNeurons) {
		outputs.push_back(tanh(neuron.lastActionPotenzial));
	}

	return MultiMatrix {{outputs}};
}
