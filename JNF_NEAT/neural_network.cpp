#include "neural_network.h"
#include "genome.h"
#include <cmath>
#include <stdexcept>


NeuralNetwork::NeuralNetwork(const TrainingParameters & parameters):
	parameters(parameters),
	genome(parameters)
{
	GenerateOnlyEssentialGenes();
	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const TrainingParameters & parameters, const Genome& genome):
	parameters(parameters),
    genome(genome)
{
    GenerateOnlyEssentialGenes();
    BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const TrainingParameters & parameters, Genome&& genome):
	parameters(parameters),
	genome(genome)
{
	ReadNumberOfInputsAndOutputsFromGenes();
	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& other) :
	parameters(other.parameters),
	genome(other.genome),
	neurons(other.neurons),
	inputNeurons(other.inputNeurons.size()),
	outputNeurons(other.outputNeurons.size())
{
	InterpretInputsAndOutputs();
}

NeuralNetwork::NeuralNetwork(NeuralNetwork&& other) :
	parameters(std::move(other.parameters)),
	genome(std::move(other.genome)),
	neurons(std::move(other.neurons)),
	inputNeurons(std::move(other.inputNeurons.size())),
	outputNeurons(std::move(other.outputNeurons.size()))
{
	InterpretInputsAndOutputs();
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

void NeuralNetwork::GenerateOnlyEssentialGenes() {
    if (genome.GetGeneCount() != inputNeurons.size() * outputNeurons.size()) {
        throw std::out_of_range("Number of inputs provided doesn't match genetic information");
    }

    auto *currentGene = &genome[0];
    for (auto in = 0U; in < inputNeurons.size(); ++in) {
        for (auto out = inputNeurons.size(); out < inputNeurons.size() + outputNeurons.size(); ++out) {
            currentGene->from = in;
            currentGene->to = out;
            currentGene->isEnabled = true;

            ++currentGene;
        }
    }
}

void NeuralNetwork::ReadNumberOfInputsAndOutputsFromGenes() {
    size_t numberOfInputs = 1;
    size_t numberOfOutputs = 1;

    // TODO jnf
    // This is awful, rewrite it
    auto i = numberOfInputs;
    for (; i < genome.GetGeneCount(); ++i) {
        if (genome[i].from == genome[i - 1U].from + 1U) {
            numberOfInputs++;
        }
        else
        if (genome[i].from != genome[i - 1U].from) {
            break;
        }
    }
    numberOfOutputs = genome[i - 1U].to - numberOfInputs;
    inputNeurons.resize(numberOfInputs);
    inputNeurons.resize(numberOfOutputs);
}

void NeuralNetwork::BuildNetworkFromGenes() {
    DeleteAllNeurons();

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
    std::vector<float> outputs(outputNeurons.size());
	for(size_t i = 0U; i < outputs.size(); ++i){
		outputs[i] = outputNeurons[i]->RequestDataAndGetActionPotential();
	}
	return outputs;
}

void NeuralNetwork::DeleteAllNeurons() {
	neurons.clear();
	for (auto in : inputNeurons) {
		in = nullptr;
	}
	for (auto out : outputNeurons) {
		out = nullptr;
	}
}

void NeuralNetwork::InterpretInputsAndOutputs()
{
	for (auto i = 0U; i < inputNeurons.size(); i++) {
		inputNeurons[i] = &neurons[i];
	}
	for (auto i = 0U; i < outputNeurons.size(); i++) {
		outputNeurons[i] = &neurons[genome[i * outputNeurons.size()].to];
	}
}