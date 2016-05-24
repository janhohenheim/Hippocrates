#include "neural_network.h"
#include <cmath>
#include <algorithm>
#include <map>


NeuralNetwork::NeuralNetwork(const TrainingParameters & parameters):
	parameters(parameters),
	genome(parameters),
	inputNeurons(parameters.numberOfInputs),
	outputNeurons(parameters.numberOfOutputs)
{
	MutateGenesAndBuildNetwork();
}

NeuralNetwork::NeuralNetwork(const Genome& genome):
	parameters(genome.GetTrainingParameters()),
    genome(genome),
	inputNeurons(genome.GetTrainingParameters().numberOfInputs),
	outputNeurons(genome.GetTrainingParameters().numberOfOutputs)
{
	MutateGenesAndBuildNetwork();
}

NeuralNetwork::NeuralNetwork(Genome&& genome):
	parameters(genome.GetTrainingParameters()),
	genome(std::move(genome)),
	inputNeurons(genome.GetTrainingParameters().numberOfInputs),
	outputNeurons(genome.GetTrainingParameters().numberOfOutputs)
{
	MutateGenesAndBuildNetwork();
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
    const_cast<TrainingParameters&>(this->parameters) = other.parameters;

	InterpretInputsAndOutputs();
	return *this;
}


void NeuralNetwork::BuildNetworkFromGenes()
{
    neurons.resize(genome.ExtrapolateNeuronCount());
    for (const auto& gene : genome) {
        if (gene.isEnabled) {
            neurons[gene.to].AddConnection(&neurons[gene.from], gene.weight);
        }
    }
    InterpretInputsAndOutputs();
}

void NeuralNetwork::SetInputs(const std::vector<float>& inputs)
{
	if (inputNeurons.size() != inputs.size()) {
		throw std::out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for(size_t i = 0U; i < inputNeurons.size(); ++i) {
		inputNeurons[i]->SetInput(inputs[i]);
	};
}

std::vector<float> NeuralNetwork::GetOutputs()
{
    std::vector<float> outputs;
    outputs.reserve(outputNeurons.size());
	for(auto& outputNeuron : outputNeurons) {
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

bool NeuralNetwork::DidChanceOccure(float chance) {
	auto num = rand() % 100;
	return num < int(100.0f * chance);
}

size_t NeuralNetwork::GetRandomNumberBetween(size_t min, size_t max)
{
    if (min == max) {
        return min;
    }
    return rand() % (max - min) + min;
}

void NeuralNetwork::AddRandomNeuron() {
	Gene* randGene = nullptr;
	do {
		size_t num = rand() % genome.GetGeneCount();
		randGene = &genome[num];
	} while (!randGene->isEnabled);

	auto indexOfNewNeuron = genome.ExtrapolateNeuronCount();

	Gene g1;
	g1.from = randGene->from;
	g1.to = indexOfNewNeuron;
	g1.weight = randGene->weight;
	g1.isEnabled = true;

	Gene g2;
	g2.from = indexOfNewNeuron;
	g2.to = randGene->to;
	g2.weight = randGene->weight;
	g2.isEnabled = true;

	randGene->isEnabled = false;

	genome.AppendGene(std::move(g1));
	genome.AppendGene(std::move(g2));
}

void NeuralNetwork::AddRandomConnection() {
	// TODO jnf: Implement a better solution
	for (auto* out : outputNeurons){
		CategorizeNeuronBranchIntoLayers(*out);
	}
	std::map<size_t, std::vector<Neuron*>> layerMap;
	for (auto& neuron : neurons) {
		layerMap[neuron.GetDistanceToOutputs()].push_back(&neuron);
	}
	auto highestLayer = layerMap.rbegin()->first + 1U;
	auto fromLayer = rand() % (highestLayer - 1U) + 1U;
	auto toLayer = rand() % (fromLayer);
	auto fromNeuron = layerMap[fromLayer][rand() % layerMap[fromLayer].size()];
	auto toNeuron = layerMap[toLayer][rand() % layerMap[toLayer].size()];
	Gene newConnection;
	newConnection.isEnabled = true;
	size_t geneticalGeneIndex = 0U;
	while (&neurons[geneticalGeneIndex++] != fromNeuron);
	newConnection.from = geneticalGeneIndex - 1U;
	geneticalGeneIndex = 0U;
	while (&neurons[geneticalGeneIndex++] != toNeuron);
	newConnection.to = geneticalGeneIndex - 1U;

	if (!genome.DoesContainGene(newConnection)) {
		toNeuron->AddConnection(fromNeuron, newConnection.weight);
		genome.AppendGene(std::move(newConnection));
	}
}

void NeuralNetwork::ShuffleWeights() {
	for (size_t i = 0; i < genome.GetGeneCount(); i++) {
		if (ShouldMutateWeight()) {
			MutateWeightOfGeneAt(i);
		}
	}
}

void NeuralNetwork::MutateWeightOfGeneAt(size_t index) {
	if (DidChanceOccure(parameters.advanced.mutation.chanceOfTotalWeightReset)) {
		genome[index].SetRandomWeight();
	} else {
		PerturbWeightAt(index);
	}
}

void NeuralNetwork::PerturbWeightAt(size_t index) {
	constexpr float perturbanceBoundaries = 0.5f;
	auto perturbance = (float)(rand() % 10'000) / 9'999.0f * perturbanceBoundaries;
	if (rand() % 2) {
		perturbance = -perturbance;
	}
	genome[index].weight += perturbance;
	if (genome[index].weight < -1.0f) {
		genome[index].weight = -1.0f;
	}
	else
	if (genome[index].weight > 1.0f) {
		genome[index].weight = 1.0f;
	}
}

void NeuralNetwork::MutateGenesAndBuildNetwork() {
	if (ShouldAddConnection()) {
		BuildNetworkFromGenes();
		AddRandomConnection();
	} else
	if (ShouldAddNeuron()) {
		AddRandomNeuron();
		BuildNetworkFromGenes();
	}
	else {
		ShuffleWeights();
		BuildNetworkFromGenes();
	}
}

void NeuralNetwork::CategorizeNeuronBranchIntoLayers(Neuron &currNode, size_t currLayer) {
	currNode.SetDistanceToOutputs(currLayer);
	for (auto &in : currNode.GetConnections()) {
		CategorizeNeuronBranchIntoLayers(*in.first, currLayer + 1U);
	}
}