#include "neural_network.h"


NeuralNetwork::NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs):
inputs(numberOfInputs),
outputs(numberOfOutputs)
{
	// TODO jnf
	// Generate Standard genes
}

NeuralNetwork::NeuralNetwork(std::vector<Gene>& genes)
{
	this->genes = std::move(genes);
	// TODO jnf
	// Fill Input Vector with empty inputs based on genes
	// Fill Output Vector with empty inputs based on genes
}

void NeuralNetwork::SetInputs(std::vector<double> & inputs)
{
	if (this->inputs.size() != inputs.size())
	{
		throw invalid_inputs_exception();
	}
	this->inputs = std::move(inputs);
	areOutputsUpToDate = false;
}

const std::vector<double> & NeuralNetwork::GetOrCalculateOutputs()
{
	if (areOutputsUpToDate) {
		return outputs;
	}
	// TODO jnf
	// Implement
	return{};
}

unsigned NeuralNetwork::GetNumberOfInputs() const
{
	return inputs.size();
}

unsigned NeuralNetwork::GetNumberOfOutputs() const
{
	return outputs.size();
}
