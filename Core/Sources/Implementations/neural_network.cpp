#include <algorithm>
#include <functional>
#include <iostream>
#include <cstring>
#include "../Headers/neural_network.hpp"
#include "../Headers/jsmn.h"

using namespace Hippocrates;
using namespace std;
NeuralNetwork::NeuralNetwork(const Genome& genome) :
	genome{genome}
{
	BuildNetworkFromGenes();
}
NeuralNetwork::NeuralNetwork(Genome&& genome) :
	genome {std::move(genome)}
{
	BuildNetworkFromGenes();
}
NeuralNetwork::NeuralNetwork(const Genome& genome, InnovationCacher& currGenerationInnovations) :
	genome(genome)
{
	MutateGenesAndBuildNetwork(currGenerationInnovations);
}

NeuralNetwork::NeuralNetwork(Genome&& genome, InnovationCacher& currGenerationInnovations) :
	genome(move(genome))
{
	MutateGenesAndBuildNetwork(currGenerationInnovations);
}

NeuralNetwork::NeuralNetwork(const std::string& json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	auto token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (size_t i = 0; i < token_count - 1; i++) {
		auto key = json.substr(tokens[i].start, tokens[i].end - tokens[i].start);
		auto value = json.substr(tokens[i + 1].start, tokens[i + 1].end - tokens[i + 1].start);

		if (key == "genome") {
			genome = Genome(value);
		} else
		if (key == "neurons") {
			neurons = ParseNeuronsJson(value);
		}
	}

	BuildNetworkFromGenes();
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& other) :
	genome(other.genome)
{
	BuildNetworkFromGenes();
}

auto NeuralNetwork::operator=(const NeuralNetwork& other) -> NeuralNetwork& {
	genome = other.genome;
	neurons.clear();
	neurons.reserve(other.neurons.size());
	layerMap.clear();
	BuildNetworkFromGenes();
	return *this;
}

auto NeuralNetwork::BuildNetworkFromGenes() -> void {
	neurons.resize(genome.GetNeuronCount());
	for (const auto& gene : genome) {
		if (gene.isEnabled) {
			Neuron::Connection in;
			in.weight = gene.weight;
			in.isRecursive = gene.isRecursive;
			in.neuron = &neurons[gene.from];
			neurons[gene.to].AddConnection(move(in));

			Neuron::Connection out;
			out.weight = gene.weight;
			out.isRecursive = gene.isRecursive;
			out.neuron = &neurons[gene.to];
			out.outGoing = true;
			neurons[gene.from].AddConnection(move(out));
		}
	}

	for (auto i = 0U; i < GetTrainingParameters().structure.numberOfBiasNeurons; i++) {
		neurons[i].SetInput(1.0f);
	}

	CategorizeNeuronsIntoLayers();
}

auto NeuralNetwork::SetInputs(Type::neuron_values_t inputs) -> void {
	auto inputNeurons = GetInputNeurons();
	if (inputNeurons.size() != inputs.size()) {
		throw out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for (size_t i = 0U; i < inputNeurons.size(); ++i) {
		inputNeurons[i]->SetInput(move(inputs[i]));
	};
}

auto NeuralNetwork::GetOutputs() -> Type::neuron_values_t {
	for (size_t i = 1; i < layerMap.size() - 1; ++i) {
		for (auto& neuron : layerMap[i]) {
			neuron->RequestDataAndGetActionPotential();
		}
	}
	Type::neuron_values_t outputs;
	const auto outputNeurons = GetOutputNeurons();
	outputs.reserve(outputNeurons.size());
	for (auto& outputNeuron : outputNeurons) {
		outputs.push_back(outputNeuron->RequestDataAndGetActionPotential());
	}
	return outputs;
}

auto Hippocrates::NeuralNetwork::GetOutputNeurons() -> std::vector<Neuron*> {
	return GetNeuronsByRangeAndIndex(genome.GetOutputCount(), [&](std::size_t i) {
		return genome[i].to;
	}
	);
}

auto Hippocrates::NeuralNetwork::GetOutputNeurons() const -> std::vector<const Neuron *> {
	return GetNeuronsByRangeAndIndex(genome.GetOutputCount(), [&](std::size_t i) {
		return genome[i].to;
	}
	);
}

auto Hippocrates::NeuralNetwork::GetInputNeurons() -> std::vector<Neuron*> {
	return GetNeuronsByRangeAndIndex(genome.GetInputCount(), [&](std::size_t i) {
		return i + GetTrainingParameters().structure.numberOfBiasNeurons;
	}
	);
}

auto Hippocrates::NeuralNetwork::GetInputNeurons() const -> std::vector<const Neuron *> {
	return GetNeuronsByRangeAndIndex(genome.GetInputCount(), [&](std::size_t i) {
		return i + GetTrainingParameters().structure.numberOfBiasNeurons;
	}
	);
}

auto NeuralNetwork::GetOutputsUsingInputs(Type::neuron_values_t inputs) -> Type::neuron_values_t {
	SetInputs(move(inputs));
	return GetOutputs();
}

auto NeuralNetwork::ShouldAddNeuron() const -> bool {
	return Utility::DidChanceOccure(
		GetTrainingParameters().		
		mutation.
		chanceForNeuralMutation
	);
}

auto NeuralNetwork::ShouldAddConnection() const -> bool {
	const auto chance = 
		GetTrainingParameters().
		mutation.
		chanceForConnectionalMutation;
	if (!Utility::DidChanceOccure(chance)) {
		return false;
	}

	const auto inputLayerSize = genome.GetInputCount() + GetTrainingParameters().structure.numberOfBiasNeurons;
	const auto outputLayerSize = genome.GetOutputCount();
	const auto hiddenLayerSize = genome.GetNeuronCount() - inputLayerSize - outputLayerSize;

	
	const auto startingConnections = inputLayerSize * outputLayerSize;
	auto hiddenConnections = hiddenLayerSize * (hiddenLayerSize - 1);
	if (!GetTrainingParameters().structure.allowRecurrentConnections) {
		hiddenConnections /= 2;
	}
	const auto connectionsFromInputs = inputLayerSize * hiddenLayerSize;
	auto connectionsToOutputs = outputLayerSize * hiddenLayerSize;
	if (GetTrainingParameters().structure.allowRecurrentConnections) {
		connectionsToOutputs *= 2;
	}

	const auto possibleConnections = 
		startingConnections + 
		hiddenConnections +
		connectionsFromInputs + 
		connectionsToOutputs;
	return genome.GetGeneCount() < possibleConnections;
}

auto NeuralNetwork::ShouldMutateWeight() const -> bool {
	return Utility::DidChanceOccure(
		GetTrainingParameters().		
		mutation.
		chanceForWeightMutation
	);
}

auto NeuralNetwork::AddRandomNeuron(InnovationCacher& currGenerationInnovations) -> void {
	auto& randGene = GetRandomEnabledGene();
	auto indexOfNewNeuron = genome.GetNeuronCount();

	Gene g1;
	g1.from = randGene.from;
	g1.to = indexOfNewNeuron;
	g1.weight = 1.0f;
	g1.isRecursive = randGene.isRecursive;
	currGenerationInnovations.AssignAndCacheHistoricalMarking(g1);

	Gene g2;
	g2.from = indexOfNewNeuron;
	g2.to = randGene.to;
	g2.weight = randGene.weight;
	g2.isRecursive = randGene.isRecursive;
	currGenerationInnovations.AssignAndCacheHistoricalMarking(g2);

	randGene.isEnabled = false;

	genome.AppendGene(move(g1));
	genome.AppendGene(move(g2));
}

auto NeuralNetwork::AddRandomConnection(InnovationCacher& currGenerationInnovations) -> void {
	// Data
	auto NeuronPair(GetTwoUnconnectedNeurons());
	auto& fromNeuron = NeuronPair.first;
	auto& toNeuron = NeuronPair.second;

	// Gene
	Gene newConnectionGene;
	newConnectionGene.from = std::distance(&*neurons.begin(), &fromNeuron);
	newConnectionGene.to = std::distance(&*neurons.begin(), &toNeuron);

	if (fromNeuron.GetLayer() > toNeuron.GetLayer()) {
		if (!GetTrainingParameters().structure.allowRecurrentConnections) {
			throw std::runtime_error("Created illegal recurrent connection");
		}
		newConnectionGene.isRecursive = true;
	}

	currGenerationInnovations.AssignAndCacheHistoricalMarking(newConnectionGene);

	// Connection
	Neuron::Connection in;
	in.isRecursive = newConnectionGene.isRecursive;
	in.neuron = &fromNeuron;
	in.weight = newConnectionGene.weight;
	toNeuron.AddConnection(move(in));

	Neuron::Connection out;
	out.isRecursive = newConnectionGene.isRecursive;
	out.neuron = &toNeuron;
	out.weight = newConnectionGene.weight;
	out.outGoing = true;
	fromNeuron.AddConnection(move(out));

	genome.AppendGene(move(newConnectionGene));
	CategorizeNeuronsIntoLayers();
}

auto NeuralNetwork::GetTwoUnconnectedNeurons() -> pair<Neuron&, Neuron&> {
	using NeuronRefs = vector<std::reference_wrapper<Neuron>>;
	NeuronRefs possibleFromNeurons(neurons.begin(), neurons.end());

	auto inputRange = genome.GetInputCount() + GetTrainingParameters().structure.numberOfBiasNeurons;
	NeuronRefs possibleToNeurons(neurons.begin() + inputRange, neurons.end());

	Utility::Shuffle(possibleFromNeurons);
	Utility::Shuffle(possibleToNeurons);


	for (auto from : possibleFromNeurons) {
		for (auto to : possibleToNeurons) {
			if (CanNeuronsBeConnected(from, to)) {
				return{ from, to };
			}
		}
	}

	throw runtime_error("Tried to get two unconnected Neurons while every neuron is already connected");
}

auto Hippocrates::NeuralNetwork::CanNeuronsBeConnected(const Neuron& lhs, const Neuron& rhs) const -> bool {
	auto areNeuronsTheSame = &lhs == &rhs;
	auto canBeConnected =
	   !areNeuronsTheSame
	&& !AreBothNeuronsOutputs(lhs, rhs)
	&& !AreNeuronsConnected(lhs, rhs);

	if (!GetTrainingParameters().structure.allowRecurrentConnections) {
		auto isRecurrent = lhs.GetLayer() > rhs.GetLayer();
		canBeConnected = canBeConnected && !isRecurrent;
	}

	return canBeConnected;
}

auto NeuralNetwork::AreBothNeuronsOutputs(const Neuron& lhs, const Neuron& rhs) const -> bool {
	bool isLhsOutput = false;
	bool isRhsOutput = false;
	for (const auto& output : GetOutputNeurons()) {
		if (output == &lhs) {
			isLhsOutput = true;
		}
		else if (output == &rhs) {
			isRhsOutput = true;
		}
		if (isLhsOutput && isRhsOutput) {
			return true;
		}
	}
	return false;
}

auto NeuralNetwork::AreNeuronsConnected(const Neuron& lhs, const Neuron & rhs) -> bool {
	for (auto& connection : rhs.GetConnections()) {
		if (!connection.outGoing && &lhs == connection.neuron) {
			return true;
		}
	}
	return false;
}

auto NeuralNetwork::ShuffleWeights() -> void {
	for (size_t i = 0; i < genome.GetGeneCount(); i++) {
		if (ShouldMutateWeight()) {
			MutateWeightOfGeneAt(i);
		}
	}
}

auto NeuralNetwork::MutateWeightOfGeneAt(size_t index) -> void {
	if (Utility::DidChanceOccure(GetTrainingParameters().mutation.chanceOfTotalWeightReset)) {
		genome[index].SetRandomWeight();
	}
	else {
		PerturbWeightAt(index);
	}
}

auto NeuralNetwork::PerturbWeightAt(size_t index) -> void {
	constexpr auto perturbRange = 2.5f;
	auto perturbance = Utility::GetRandomNumberBetween(-perturbRange, perturbRange);
	genome[index].weight += perturbance;
	// In C++17
	// std::clamp(genome[index].weight, -1.0f, 1.0f));
	if (genome[index].weight < -8.0f) {
		genome[index].weight = -8.0f;
	}
	else if (genome[index].weight > 8.0f) {
		genome[index].weight = 8.0f;
	}
	
}

auto NeuralNetwork::MutateGenesAndBuildNetwork(InnovationCacher& currGenerationInnovations) -> void {
	if (ShouldAddConnection()) {
		BuildNetworkFromGenes();
		AddRandomConnection(currGenerationInnovations);
	}
	else {
		if (ShouldAddNeuron()) {
			AddRandomNeuron(currGenerationInnovations);
		} else {
			ShuffleWeights();
		}

		BuildNetworkFromGenes();
	}
}

auto NeuralNetwork::CategorizeNeuronsIntoLayers() -> void {
	for (auto i = 0U; i < GetTrainingParameters().structure.numberOfBiasNeurons; i++) {
		CategorizeNeuronBranchIntoLayers(neurons[i]);
	}
	for (auto* in : GetInputNeurons()) {
		CategorizeNeuronBranchIntoLayers(*in);
	}

	size_t highestLayer = 0U;
	auto outputNeurons = GetOutputNeurons();
	for (auto* out : outputNeurons) {
		highestLayer = max(out->GetLayer(), highestLayer);
	}
	for (auto* out : outputNeurons) {
		out->layer = highestLayer;
	}

	for (auto& neuron : neurons) {
		layerMap[neuron.GetLayer()].push_back(&neuron);
	}
}

auto NeuralNetwork::CategorizeNeuronBranchIntoLayers(Neuron& currNode, size_t currentDepth) const -> void {
	currNode.layer = currentDepth;
	const auto nextLayer = currNode.layer + 1;


	auto HasYetToBeLayered = [&nextLayer](const auto& connection) {
		return nextLayer > connection.neuron->layer;
	};
	auto IsInHigherLayer = [](const auto& connection) {
		return (connection.outGoing != connection.isRecursive);
	};

	for (auto &connection : currNode.GetConnections()) {
		if (HasYetToBeLayered(connection) && IsInHigherLayer(connection)) {
			CategorizeNeuronBranchIntoLayers(*connection.neuron, nextLayer);
		}
	}
}

auto NeuralNetwork::GetRandomEnabledGene() -> Gene& {
	size_t num = Utility::GetRandomNumberBetween(0ULL, genome.GetGeneCount() - 1ULL);
	auto randGene = genome.begin();
	randGene += num;
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
		throw runtime_error("Could not insert neuron because every gene is disabled");
	}
	return *randGene;
}

auto NeuralNetwork::GetJSON() const -> string {
	string s("{\"neurons\":[");
	for (const auto& neuron : neurons) {
		s += neuron.GetJSON();
		s += ",";
	}
	s.pop_back();
	s += "],\"genome\":";
	s += genome.GetJSON();
	s += "}";
	return s;
}

auto NeuralNetwork::Reset() -> void {
	for (auto& neuron : neurons) {
		neuron.Reset();
	}
}

auto NeuralNetwork::ParseNeuronsJson(std::string json) -> std::vector<Neuron> {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	auto token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	vector<Neuron> neurons;

	for (size_t i = 0; i < token_count - 1; i++) {
		if (tokens[i].type == JSMN_OBJECT) {
			neurons.push_back(Neuron(json.substr(tokens[i].start, tokens[i].end - tokens[i].start)));
		}
	}

	return neurons;
}
