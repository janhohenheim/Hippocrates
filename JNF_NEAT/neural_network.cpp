#include "neural_network.h"
#include <cmath>
#include <stdexcept>


NeuralNetwork::NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs):
		genes(numberOfInputs + numberOfOutputs),
		numberOfInputs(numberOfInputs),
		numberOfOutputs(numberOfOutputs)
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

void NeuralNetwork::SetInputs(const std::vector<float> & inputs)
{
	if (inputNeurons.size() != inputs.size())
	{
		throw std::out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for(size_t i = 0U; i < inputNeurons.size(); ++i){
		inputNeurons[i]->SetInput(inputs[i]);
	};
	areOutputsUpToDate = false;
}

const std::vector<float> & NeuralNetwork::GetOrCalculateOutputs()
{
	if (areOutputsUpToDate) {
		return outputs;
	}

	for(size_t i = 0U; i < outputs.size(); ++i){
		outputs[i] = outputNeurons[i]->RequestDataAndGetActionPotential();
	}

	areOutputsUpToDate = true;
	return outputs;
}

const std::vector<Gene> & NeuralNetwork::GetGenes() const {
	return genes;
}

void NeuralNetwork::BuildNetworkFromGenes() {
	DeleteAllNeurons();

	for (const auto & gene : genes) {
		if (gene.to >= neurons.size()) {
			neurons.resize(gene.to + 1U);
		}
		if (gene.isEnabled) {
			Neuron::IncomingConnection connection;
			connection.incoming = &neurons[gene.from];
			connection.weight = gene.weight;
			neurons[gene.to].AddConnection(connection);
		}
	}
	InterpretInputsAndOutputs();

	areOutputsUpToDate = false;
}

void NeuralNetwork::DeleteAllNeurons() {
	neurons.clear();
	inputNeurons.clear();
	outputNeurons.clear();
}

void NeuralNetwork::GenerateOnlyEssentialGenes() {
	if(genes.size() != numberOfInputs * numberOfOutputs){
		throw std::out_of_range("Number of inputs provided doesn't match genetic information");
	}
	auto currentGene = &genes.front();
	for (auto in = 0U; in < numberOfInputs; ++in) {
		for (auto out = numberOfInputs; out < numberOfOutputs; ++out){
			currentGene->from = in;
			currentGene->to = out;
			currentGene->weight = GetRandomWeight();
			currentGene->isEnabled = true;

			++currentGene;
		}
	}
	areOutputsUpToDate = false;
}

float NeuralNetwork::GetRandomWeight() {
	return (float)(rand() % 100) / 100.0f;
}

void NeuralNetwork::InterpretInputsAndOutputs()
{
	for (unsigned int i = 0U; i < numberOfInputs; i++) {
		// TODO jnf
		// Does this code always work or is my logic off?
		inputNeurons[i] = &neurons[i];
		outputNeurons[i] = &neurons[genes[i * numberOfOutputs].to];
	}
}

void NeuralNetwork::ReadNumberOfInputsAndOutputsFromGenes() {
	numberOfInputs = 1U;
	numberOfOutputs = 1U;

	// TODO jnf
	// This is awful, rewrite it
	auto i = numberOfInputs;
	for (; i < genes.size(); ++i) {
		if (genes[i].from == genes[i - 1U].from + 1U) {
			numberOfInputs++;
		} else 
		if (genes[i].from != genes[i - 1U].from) {
			break;
		}
	}
	numberOfOutputs = genes[i - 1U].to - numberOfInputs;
}













