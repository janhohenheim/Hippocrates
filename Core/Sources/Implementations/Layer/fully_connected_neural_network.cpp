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
				Connection connection(inputNeurons[i * multiMatrix.GetElementCount() + j], outputNeurons[k]);
				outputNeurons[k].AddConnection(connection);
			}
		}
	}

	std::size_t currentNeuron = 0;
	for (const auto& subMatrix : multiMatrix) {
		for (auto input : subMatrix) {
			inputNeurons[currentNeuron].lastActionPotential = input;
			currentNeuron++;
		}
	}

	for (auto neuron : outputNeurons) {
		for (auto connection : neuron.connections) {
			neuron.lastActionPotential += connection.from.lastActionPotential * connection.weight;
		}

		neuron.lastActionPotential = tanh(neuron.lastActionPotential);
	}

	Matrix::Size size;
	size.width = nOutputs;
	size.height = 1;

	Matrix outputs(size);

	for (std::size_t i = 0; i < nOutputs; i++) {
		outputs.ElementAt({i, 0}) = outputNeurons[i].lastActionPotential;
	}

	return MultiMatrix {{outputs}};
}
