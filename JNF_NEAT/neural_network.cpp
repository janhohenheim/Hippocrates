#include "neural_network.h"
#include "gene_examinator.h"
#include <cmath>
#include <stdexcept>


NeuralNetwork::NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs):
		genes(numberOfInputs * numberOfOutputs),
		inputNeurons(numberOfInputs),
		outputNeurons(numberOfOutputs)
{
	GenerateOnlyEssentialGenes();
	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const std::vector<Gene> & genes):
    genes(genes)
{
    GenerateOnlyEssentialGenes();
    BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(std::vector<Gene> && genes):
	genes(genes)
{
	ReadNumberOfInputsAndOutputsFromGenes();
	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork & other) :
	genes(other.genes),
	neurons(other.neurons),
	inputNeurons(other.inputNeurons.size()),
	outputNeurons(other.outputNeurons.size())
{
	InterpretInputsAndOutputs();
}

NeuralNetwork::NeuralNetwork(NeuralNetwork && other) :
	genes(std::move(other.genes)),
	neurons(std::move(other.neurons)),
	inputNeurons(std::move(other.inputNeurons.size())),
	outputNeurons(std::move(other.outputNeurons.size()))
{
	InterpretInputsAndOutputs();
}

NeuralNetwork & NeuralNetwork::operator=(const NeuralNetwork & other)
{
	genes = other.genes;
	neurons = other.neurons;
	inputNeurons.resize(other.inputNeurons.size());
	outputNeurons.resize(other.outputNeurons.size());

	InterpretInputsAndOutputs();
	return *this;
}

void NeuralNetwork::GenerateOnlyEssentialGenes() {
    if (genes.size() != inputNeurons.size() * outputNeurons.size()) {
        throw std::out_of_range("Number of inputs provided doesn't match genetic information");
    }
    auto currentGene = &genes.front();
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
    for (; i < genes.size(); ++i) {
        if (genes[i].from == genes[i - 1U].from + 1U) {
            numberOfInputs++;
        }
        else
        if (genes[i].from != genes[i - 1U].from) {
            break;
        }
    }
    numberOfOutputs = genes[i - 1U].to - numberOfInputs;
    inputNeurons.resize(numberOfInputs);
    inputNeurons.resize(numberOfOutputs);
}

void NeuralNetwork::BuildNetworkFromGenes() {
    DeleteAllNeurons();

    neurons.resize(GeneExaminator::GetNumberOfNeuronsInGenes(genes));
    for (const auto & gene : genes) {
        if (gene.isEnabled) {
            Neuron::IncomingConnection connection;
            connection.incoming = &neurons[gene.from];
            connection.weight = gene.weight;
            neurons[gene.to].AddConnection(std::move(connection));
        }
    }
    InterpretInputsAndOutputs();
}

void NeuralNetwork::SetInputs(const std::vector<float> & inputs)
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

const std::vector<Gene> & NeuralNetwork::GetGenes() const {
	return genes;
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
		outputNeurons[i] = &neurons[genes[i * outputNeurons.size()].to];
	}
}