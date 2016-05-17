#include "neural_network.h"
#include <cmath>
#include <stdexcept>


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
	/*
    auto GetRandomNumberBetween = [](size_t min, size_t max) {
        if (min == max){
            return min;
        }
        return rand() % (max - min) + min;
    };
    Gene newConnection;
    auto highestIndex = GetGeneCount() - 1U;
    auto randIndex = GetRandomNumberBetween(0U, highestIndex - 1U);
    newConnection.from = genes[randIndex].from;
    randIndex = GetRandomNumberBetween(randIndex + 1, highestIndex);
    newConnection.to = genes[randIndex].to;
    if (newConnection.from == newConnection.to) {
        AddRandomConnection();
    }
    else {
        genes.push_back(std::move(newConnection));
    }
    */
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
	constexpr float perturbanceBoundaries = 0.2f;
	auto perturbance = (float)(rand() % 10'000) / 10'000.0f * perturbanceBoundaries;
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
		AddRandomConnection();
		BuildNetworkFromGenes();
	}
	else
	if (ShouldAddNeuron()) {
		BuildNetworkFromGenes();
		AddRandomNeuron();
	}
	else {
		ShuffleWeights();
		BuildNetworkFromGenes();
	}
}


