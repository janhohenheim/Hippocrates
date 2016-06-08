#include "neural_network.h"
#include <cmath>
#include <algorithm>
#include <map>


NeuralNetwork::NeuralNetwork(const TrainingParameters & parameters, bool shouldMutate):
	parameters(parameters),
	genome(parameters),
	inputNeurons(parameters.numberOfInputs),
	outputNeurons(parameters.numberOfOutputs)
{
	if (shouldMutate) {
		MutateGenesAndBuildNetwork();
	} else {
		BuildNetworkFromGenes();
	}
}

NeuralNetwork::NeuralNetwork(Genome genome, bool shouldMutate):
	parameters(genome.GetTrainingParameters()),
	genome(std::move(genome)),
	inputNeurons(genome.GetTrainingParameters().numberOfInputs),
	outputNeurons(genome.GetTrainingParameters().numberOfOutputs)
{
	if (shouldMutate) {
		MutateGenesAndBuildNetwork();
	} else {
		BuildNetworkFromGenes();
	}
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

NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& other) {
	layerMap = other.layerMap;
	genome = other.genome;
	neurons = other.neurons;
	inputNeurons.resize(other.inputNeurons.size());
	outputNeurons.resize(other.outputNeurons.size());
	const_cast<TrainingParameters&>(this->parameters) = other.parameters;

	InterpretInputsAndOutputs();
	return *this;
}

void NeuralNetwork::BuildNetworkFromGenes() {
	neurons.resize(genome.GetNeuronCount());
	for (const auto& gene : genome) {
		if (gene.isEnabled) {
			Neuron::IncomingConnection connection;
			connection.neuron = &neurons[gene.from];
			connection.weight = gene.weight;
			connection.isRecursive = gene.isRecursive;
			neurons[gene.to].AddConnection(std::move(connection));
		}
	}
	InterpretInputsAndOutputs();
	CategorizeNeuronsIntoLayers();
}

void NeuralNetwork::SetInputs(const std::vector<float>& inputs) {
	if (inputNeurons.size() != inputs.size()) {
		throw std::out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for(size_t i = 0U; i < inputNeurons.size(); ++i) {
		inputNeurons[i]->SetInput(inputs[i]);
	};
}

std::vector<float> NeuralNetwork::GetOutputs() {
	for (size_t i = 1; i < layerMap.size() - 1; ++i) {
		for (auto& neuron : layerMap[i]){
			neuron->RequestDataAndGetActionPotential();
		}
	}
	std::vector<float> outputs;
	outputs.reserve(outputNeurons.size());
	for(auto& outputNeuron : outputNeurons) {
		outputs.push_back(outputNeuron->RequestDataAndGetActionPotential());
	}
	return outputs;
}

std::vector<float> NeuralNetwork::GetOutputs(const std::vector<float>& inputs) {
	SetInputs(inputs);
	return GetOutputs();
}

void NeuralNetwork::InterpretInputsAndOutputs() {
	// Bias
	for (auto i = 0U; i < parameters.advanced.structure.numberOfBiasNeurons; i++) {
		neurons[i].SetInput(1.0f);
	}

	// Inputs
	for (auto i = 0U; i < parameters.numberOfInputs; i++) {
		inputNeurons[i] = &neurons[i + parameters.advanced.structure.numberOfBiasNeurons];
	}

	// Outputs
	for (auto i = 0U; i < parameters.numberOfOutputs; i++) {
		outputNeurons[i] = &neurons[genome[i * parameters.numberOfOutputs].to];
	}
}

bool NeuralNetwork::ShouldAddConnection() const {
	const bool hasChanceOccured = DidChanceOccure(parameters.advanced.mutation.chanceForConnectionalMutation);
	const bool hasSpaceForNewConnections = GetGenome().GetNeuronCount() > (parameters.numberOfInputs + parameters.numberOfOutputs + parameters.advanced.structure.numberOfBiasNeurons);
	return hasChanceOccured && hasSpaceForNewConnections;
}

bool NeuralNetwork::DidChanceOccure(float chance) {
	auto num = rand() % 100;
	return num < int(100.0f * chance);
}

size_t NeuralNetwork::GetRandomNumberBetween(size_t min, size_t max) {
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
	g1.weight = 1.0f;
	g1.isRecursive = randGene.isRecursive;

	Gene g2;
	g2.from = indexOfNewNeuron;
	g2.to = randGene.to;
	g2.weight = randGene.weight;
	g2.isRecursive = randGene.isRecursive;

	randGene.isEnabled = false;

	genome.AppendGene(std::move(g1));
	genome.AppendGene(std::move(g2));
}

void NeuralNetwork::AddRandomConnection() {
	size_t fromNeuronIndex = rand() % neurons.size();
	auto inputRange = parameters.advanced.structure.numberOfBiasNeurons + parameters.numberOfInputs;
	size_t toNeuronIndex = (rand() % (neurons.size() - inputRange)) + inputRange;
	if (fromNeuronIndex == toNeuronIndex) {
		if (fromNeuronIndex < (neurons.size() - 1)) {
			fromNeuronIndex++;
		} else {
			fromNeuronIndex--;
		}
	}
   
	auto& fromNeuron = neurons[fromNeuronIndex];
	auto& toNeuron = neurons[toNeuronIndex];
	Gene newConnectionGene;
	if (fromNeuron.GetLayer() <= toNeuron.GetLayer()){
		newConnectionGene.from = fromNeuronIndex;
		newConnectionGene.to = toNeuronIndex;
	} else {
		newConnectionGene.from = toNeuronIndex;
		newConnectionGene.to = fromNeuronIndex;
		newConnectionGene.isRecursive = true;
	}
	if (!genome.DoesContainGene(newConnectionGene)) {
		Neuron::IncomingConnection newConnection;
		newConnection.isRecursive = newConnectionGene.isRecursive;
		newConnection.neuron = &fromNeuron;
		newConnection.weight = newConnectionGene.weight;

		genome.AppendGene(std::move(newConnectionGene));
		toNeuron.AddConnection(std::move(newConnection));
		CategorizeNeuronsIntoLayers();
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
	} else
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

void NeuralNetwork::CategorizeNeuronsIntoLayers() {
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

	for (auto& neuron : neurons) {
		layerMap[neuron.GetLayer()].push_back(&neuron);
	}
}

void NeuralNetwork::CategorizeNeuronBranchIntoLayers(Neuron& currNode) {
	for (auto &in : currNode.GetConnections()) {
		if (!in.isRecursive) {
			CategorizeNeuronBranchIntoLayers(*in.neuron);
			currNode.SetLayer(in.neuron->GetLayer() + 1);
		}
	}
}

Gene& NeuralNetwork::GetRandomEnabledGene() {
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