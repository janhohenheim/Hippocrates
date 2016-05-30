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
	neurons.resize(genome.GetNeuronCount());
	for (const auto& gene : genome) {
		if (gene.isEnabled) {
            Neuron::IncomingConnection connection;
            connection.neuron = &neurons[gene.from];
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
		inputNeurons[i]->SetInput(0.0f);
	}
	for (auto i = 0U; i < parameters.numberOfOutputs; i++) {
		outputNeurons[i] = &neurons[genome[i * parameters.numberOfOutputs].to];
		inputNeurons[i]->SetInput(0.0f);
	}
}

bool NeuralNetwork::ShouldAddConnection() const
{
	const bool hasChanceOccured = DidChanceOccure(parameters.advanced.mutation.chanceForConnectionalMutation);
	const bool hasSpaceForNewConnections = GetGenome().GetNeuronCount() > (parameters.numberOfInputs + parameters.numberOfOutputs);
	return hasChanceOccured && hasSpaceForNewConnections;
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
	auto& randGene = GetRandomEnabledGene();
	auto indexOfNewNeuron = genome.GetNeuronCount();

	Gene g1;
	g1.from = randGene.from;
	g1.to = indexOfNewNeuron;
	g1.weight = randGene.weight;

	Gene g2;
	g2.from = indexOfNewNeuron;
	g2.to = randGene.to;
	g2.weight = randGene.weight;

	randGene.isEnabled = false;

	genome.AppendGene(std::move(g1));
	genome.AppendGene(std::move(g2));
}

void NeuralNetwork::AddRandomConnection() {
	CategorizeNeuronsIntoLayers();	
	std::map<size_t, std::vector<Neuron*>> layerMap;
	for (auto& neuron : neurons) {
		layerMap[neuron.GetLayer()].push_back(&neuron);
	}


	auto highestLayer = layerMap.rbegin()->first + 1U;
	auto fromLayer = rand() % (highestLayer - 1U);
	auto toLayer = GetRandomNumberBetween(fromLayer + 1U, highestLayer);
	auto fromNeuron = layerMap[fromLayer][rand() % layerMap[fromLayer].size()];
	auto toNeuron = layerMap[toLayer][rand() % layerMap[toLayer].size()];
	
	
	Gene connectionalGene;
	size_t geneticalGeneIndex = 0U;
	while (&neurons[geneticalGeneIndex++] != fromNeuron);
    connectionalGene.from = geneticalGeneIndex - 1U;
	geneticalGeneIndex = 0U;
	while (&neurons[geneticalGeneIndex++] != toNeuron);
    connectionalGene.to = geneticalGeneIndex - 1U;


	if (!genome.DoesContainGene(connectionalGene)) {
        Neuron::IncomingConnection connection;
        connection.neuron = fromNeuron;
        connection.weight = connectionalGene.weight;
		toNeuron->AddConnection(std::move(connection));
		genome.AppendGene(std::move(connectionalGene));
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
	} 
	else {
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
	} else
	if (genome[index].weight > 1.0f) {
		genome[index].weight = 1.0f;
	}
}

void NeuralNetwork::MutateGenesAndBuildNetwork() {
	if (ShouldAddConnection()) {
		/*
		// TODO jnf: Delete this
		Genome mockGenome(parameters);
		mockGenome.GetGeneAt(mockGenome.GetGeneCount() - 1).isEnabled = false;
		auto AddMockGene = [&](size_t from, size_t to, bool isEnabled = true) {
			Gene mockGene;
			mockGene.from = from;
			mockGene.to = to;
			mockGene.isEnabled = isEnabled;
			mockGenome.AppendGene(mockGene);
		};
		AddMockGene(1, 3);
		AddMockGene(3, 2, false);
		AddMockGene(3, 4);
		AddMockGene(4, 2, false);
		AddMockGene(0, 4);
		AddMockGene(3, 5);
		AddMockGene(5, 4);
		AddMockGene(5, 2);
		AddMockGene(4, 6);
		AddMockGene(6, 2, false);
		AddMockGene(6, 7);
		AddMockGene(7, 2);
		// Was observed to generate from = 6, to = 5
		genome = mockGenome;
		*/
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

void NeuralNetwork::CategorizeNeuronsIntoLayers()
{
	for (auto* out : outputNeurons) {
		CategorizeNeuronBranchIntoLayers(*out);
	}
	size_t highestLayer = 0U;
	for (auto* out : outputNeurons) {
		if (out->GetLayer() > highestLayer) {
			highestLayer = out->GetLayer();
		};
	}
	for (auto* out : outputNeurons) {
		out->SetLayer(highestLayer);
	}
}

void NeuralNetwork::CategorizeNeuronBranchIntoLayers(Neuron& currNode) {
	for (auto &in : currNode.GetConnections()) {
		CategorizeNeuronBranchIntoLayers(*in.neuron);
		currNode.SetLayer(in.neuron->GetLayer() + 1);
	}
}

Gene& NeuralNetwork::GetRandomEnabledGene()
{
	size_t num = rand() % genome.GetGeneCount();
	auto& randGene = genome.begin() + num;
	while (randGene != genome.end() && !randGene->isEnabled) {
		++randGene;
	}
	if (randGene == genome.end()) {
		randGene = genome.begin() + num;
		while (randGene != genome.begin() && !randGene->isEnabled) {
			--randGene;
		}
	}
	if (!randGene->isEnabled) {
		throw std::exception("Could not insert neuron because every gene is disabled");
	}
	return *randGene;
}
