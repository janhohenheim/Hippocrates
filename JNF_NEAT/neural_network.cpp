#include "neural_network.h"
#include <cmath>
#include <stdexcept>


NeuralNetwork::NeuralNetwork(const TrainingParameters & parameters):
	parameters(parameters),
	genome(parameters),
	inputNeurons(parameters.numberOfInputs),
	outputNeurons(parameters.numberOfOutputs)
{
	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const Genome& genome):
	parameters(genome.GetTrainingParameters()),
    genome(genome),
	inputNeurons(genome.GetTrainingParameters().numberOfInputs),
	outputNeurons(genome.GetTrainingParameters().numberOfOutputs)
{
    BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(Genome&& genome):
	parameters(genome.GetTrainingParameters()),
	genome(std::move(genome)),
	inputNeurons(genome.GetTrainingParameters().numberOfInputs),
	outputNeurons(genome.GetTrainingParameters().numberOfOutputs)
{
	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& other) :
	parameters(other.parameters),
	genome(other.genome),
	neurons(other.neurons.size()),
	inputNeurons(other.inputNeurons.size()),
	outputNeurons(other.outputNeurons.size())
{
	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(NeuralNetwork&& other) :
	parameters(std::move(other.parameters)),
	genome(std::move(other.genome)),
	neurons(other.neurons.size()),
	inputNeurons(std::move(other.inputNeurons.size())),
	outputNeurons(std::move(other.outputNeurons.size()))
{
	BuildNetworkFromGenes();
}

NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& other)
{
	genome = other.genome;
	neurons = other.neurons;
	inputNeurons.resize(other.inputNeurons.size());
	outputNeurons.resize(other.outputNeurons.size());

	InterpretInputsAndOutputs();
	return *this;
}


void NeuralNetwork::BuildNetworkFromGenes()
{
    neurons.resize(genome.ExtrapolateNeuronCount());
    for (const auto& gene : genome) {
        if (gene.isEnabled) {
            Neuron::IncomingConnection connection;
            connection.incoming = &neurons[gene.from];
            connection.weight = gene.weight;
            neurons[gene.to].AddConnection(std::move(connection));
        }
    }
    InterpretInputsAndOutputs();
}

void NeuralNetwork::SetInputs(const std::vector<float>& inputs)
{
	if (inputNeurons.size() != inputs.size())
	{
		throw std::out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for(size_t i = 0U; i < inputNeurons.size(); ++i){
		inputNeurons[i]->SetInput(inputs[i]);
	};
}

std::vector<float> NeuralNetwork::GetOutputs()
{
    std::vector<float> outputs;
    outputs.reserve(outputNeurons.size());
	for(auto& outputNeuron : outputNeurons){
		outputs.push_back(outputNeuron->RequestDataAndGetActionPotential());
	}
	return outputs;
}

void NeuralNetwork::InterpretInputsAndOutputs()
{
	for (auto i = 0U; i < parameters.numberOfInputs; i++) {
		inputNeurons[i] = &neurons[i];
	}
	for (auto i = 0U; i < parameters.numberOfOutputs; i++) {
		outputNeurons[i] = &neurons[genome[i * parameters.numberOfOutputs].to];
	}
}