#include <cstdlib>
#include <cmath>
#include <stdexcept>
#include "neural_network.h"


NeuralNetwork::NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs):
genes(numberOfInputs + numberOfOutputs)
{
	GenerateOnlyEssentialGenes(numberOfInputs, numberOfOutputs);
	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const std::vector<Gene> & genes):
genes(genes)
{
	BuildNetworkFromGenes();
}

void NeuralNetwork::SetInputs(std::vector<double> & inputs)
{
	if (sensors.size() != inputs.size())
	{
		throw std::out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for(int i = 0; i < sensors.size(); ++i){
		sensors[i].Reset();
		sensors[i].AddToActionPotential(inputs[i]);
	};
	areOutputsUpToDate = false;
}

const std::vector<double> & NeuralNetwork::GetOrCalculateOutputs()
{
	if (areOutputsUpToDate) {
		return outputs;
	}

	ProcessInputLayer();
	ProcessHiddenLayers();
	ProcessOutputLayer();

	areOutputsUpToDate = true;
	return outputs;
}

void NeuralNetwork::ProcessInputLayer() {
	for(auto & sensor : sensors){
		sensor.FeedConnectedNeurons();
	}
}

void NeuralNetwork::ProcessHiddenLayers() {
	for (auto & layer : hiddenLayers){
		for (auto & hiddenNeuron : layer){
			hiddenNeuron.FeedConnectedNeurons();
		}
	}
}

void NeuralNetwork::ProcessOutputLayer() {
	for(int i = 0; i < outputs.size(); ++i){
		outputs[i] = outputNeurons[i].GetActionPotential();
	}
}

const std::vector<Gene> & NeuralNetwork::GetGenes() const {
	return genes;
}

void NeuralNetwork::BuildNetworkFromGenes() {
	// TODO jnf
	// Implement
	areOutputsUpToDate = false;
}

void NeuralNetwork::GenerateOnlyEssentialGenes(unsigned int numberOfInputs, unsigned int numberOfOutputs) {
	if(genes.size() != numberOfInputs * numberOfOutputs){
		throw std::out_of_range("Number of inputs provided doesn't match genetic information");
	}
	auto * currentGene = &genes.front();
	for (auto in = 0U; in < numberOfInputs; ++in) {
		for (auto out = 0U; out < numberOfOutputs; ++out){
			currentGene->from = in;
			currentGene->to = out;
			currentGene->weight = GetRandomWeight();
			currentGene->isEnabled = true;

			++currentGene;
		}
	}
	areOutputsUpToDate = false;
}

double NeuralNetwork::GetRandomWeight() const {
	return (double)(rand() % 100) / 100.0;
}









