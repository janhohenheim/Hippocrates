#include <algorithm>
#include <functional>
#include <iostream>
#include <cstring>

#include "phenotype/neural_network.hpp"
#include "utility/jsmn.h"
#include "utility/random.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Phenotype;

NeuralNetwork::NeuralNetwork(const Genotype::Genome& genome) :
	genome {genome}
{
	BuildNetworkFromGenes();
}
NeuralNetwork::NeuralNetwork(Genotype::Genome&& genome) :
	genome {std::move(genome)}
{
	BuildNetworkFromGenes();
}
NeuralNetwork::NeuralNetwork(const Genotype::Genome& genome, Training::InnovationCacher& currGenerationInnovations) :
	genome {genome}
{
	MutateGenesAndBuildNetwork(currGenerationInnovations);
}

NeuralNetwork::NeuralNetwork(Genotype::Genome&& genome, Training::InnovationCacher& currGenerationInnovations) :
	genome {std::move(genome)}
{
	MutateGenesAndBuildNetwork(currGenerationInnovations);
}

NeuralNetwork::NeuralNetwork(const std::string& json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	std::size_t token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (std::size_t i = 0; i < token_count - 1; i++) {
		auto key = json.substr(tokens[i].start, tokens[i].end - tokens[i].start);
		auto value = json.substr(tokens[i + 1].start, tokens[i + 1].end - tokens[i + 1].start);

		if (key == "genome") {
			genome = Genotype::Genome(value);
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

auto NeuralNetwork::operator=(const NeuralNetwork& other)& -> NeuralNetwork& {
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
			neurons[gene.to].AddConnection(std::move(in));

			Neuron::Connection out;
			out.weight = gene.weight;
			out.isRecursive = gene.isRecursive;
			out.neuron = &neurons[gene.to];
			out.outGoing = true;
			neurons[gene.from].AddConnection(std::move(out));
		}
	}

	for (auto i = 0U; i < Training::GetParameters().structure.numberOfBiasNeurons; i++) {
		neurons[i].SetInput(1.0f);
	}

	CategorizeNeuronsIntoLayers();
}

auto NeuralNetwork::SetInputs(Type::neuron_values_t inputs) -> void {
	auto inputNeurons = GetInputNeurons();
	if (inputNeurons.size() != inputs.size()) {
		throw std::out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for (std::size_t i = 0U; i < inputNeurons.size(); ++i) {
		inputNeurons[i]->SetInput(std::move(inputs[i]));
	};
}

auto NeuralNetwork::GetOutputs() -> Type::neuron_values_t {
	for (std::size_t i = 1; i < layerMap.size() - 1; ++i) {
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

auto NeuralNetwork::GetOutputNeurons() -> std::vector<Neuron*> {
	return GetNeuronsByRangeAndIndex(genome.GetOutputCount(), [&](std::size_t i) {
		return genome[i].to;
	}
	);
}

auto NeuralNetwork::GetOutputNeurons() const -> std::vector<const Neuron *> {
	return GetNeuronsByRangeAndIndex(genome.GetOutputCount(), [&](std::size_t i) {
		return genome[i].to;
	}
	);
}

auto NeuralNetwork::GetInputNeurons() -> std::vector<Neuron*> {
	return GetNeuronsByRangeAndIndex(genome.GetInputCount(), [&](std::size_t i) {
		return i + Training::GetParameters().structure.numberOfBiasNeurons;
	}
	);
}

auto NeuralNetwork::GetInputNeurons() const -> std::vector<const Neuron *> {
	return GetNeuronsByRangeAndIndex(genome.GetInputCount(), [&](std::size_t i) {
		return i + Training::GetParameters().structure.numberOfBiasNeurons;
	}
	);
}

auto NeuralNetwork::GetOutputsUsingInputs(Type::neuron_values_t inputs) -> Type::neuron_values_t {
	SetInputs(std::move(inputs));
	return GetOutputs();
}

auto NeuralNetwork::ShouldAddNeuron() const -> bool {
	return Utility::Random::DidChanceOccure(
		Training::GetParameters().		
		mutation.
		chanceForNeuralMutation
	);
}

auto NeuralNetwork::ShouldAddConnection() const -> bool {
	const auto chance = 
		Training::GetParameters().
		mutation.
		chanceForConnectionalMutation;
	if (!Utility::Random::DidChanceOccure(chance)) {
		return false;
	}

	const auto inputLayerSize = genome.GetInputCount() + Training::GetParameters().structure.numberOfBiasNeurons;
	const auto outputLayerSize = genome.GetOutputCount();
	const auto hiddenLayerSize = genome.GetNeuronCount() - inputLayerSize - outputLayerSize;

	
	const auto startingConnections = inputLayerSize * outputLayerSize;
	auto hiddenConnections = hiddenLayerSize * (hiddenLayerSize - 1);
	if (!Training::GetParameters().structure.allowRecurrentConnections) {
		hiddenConnections /= 2;
	}
	const auto connectionsFromInputs = inputLayerSize * hiddenLayerSize;
	auto connectionsToOutputs = outputLayerSize * hiddenLayerSize;
	if (Training::GetParameters().structure.allowRecurrentConnections) {
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
	return Utility::Random::DidChanceOccure(
		Training::GetParameters().		
		mutation.
		chanceForWeightMutation
	);
}

auto NeuralNetwork::AddRandomNeuron(Training::InnovationCacher& currGenerationInnovations) -> void {
	auto& randGene = GetRandomEnabledGene();
	auto indexOfNewNeuron = genome.GetNeuronCount();

	Genotype::Gene g1;
	g1.from = randGene.from;
	g1.to = indexOfNewNeuron;
	g1.weight = 1.0f;
	g1.isRecursive = randGene.isRecursive;
	currGenerationInnovations.AssignAndCacheHistoricalMarking(g1);

	Genotype::Gene g2;
	g2.from = indexOfNewNeuron;
	g2.to = randGene.to;
	g2.weight = randGene.weight;
	g2.isRecursive = randGene.isRecursive;
	currGenerationInnovations.AssignAndCacheHistoricalMarking(g2);

	randGene.isEnabled = false;

	genome.AppendGene(std::move(g1));
	genome.AppendGene(std::move(g2));
}

auto NeuralNetwork::AddRandomConnection(Training::InnovationCacher& currGenerationInnovations) -> void {
	// Data
	auto NeuronPair(GetTwoUnconnectedNeurons());
	auto& fromNeuron = NeuronPair.first;
	auto& toNeuron = NeuronPair.second;

	// Gene
	Genotype::Gene newConnectionGene;
	newConnectionGene.from = std::distance(&*neurons.begin(), &fromNeuron);
	newConnectionGene.to = std::distance(&*neurons.begin(), &toNeuron);

	if (fromNeuron.GetLayer() > toNeuron.GetLayer()) {
		if (!Training::GetParameters().structure.allowRecurrentConnections) {
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
	toNeuron.AddConnection(std::move(in));

	Neuron::Connection out;
	out.isRecursive = newConnectionGene.isRecursive;
	out.neuron = &toNeuron;
	out.weight = newConnectionGene.weight;
	out.outGoing = true;
	fromNeuron.AddConnection(std::move(out));

	genome.AppendGene(std::move(newConnectionGene));
	CategorizeNeuronsIntoLayers();
}

auto NeuralNetwork::GetTwoUnconnectedNeurons() -> std::pair<Neuron&, Neuron&> {
	using NeuronRefs = std::vector<std::reference_wrapper<Neuron>>;
	NeuronRefs possibleFromNeurons(neurons.begin(), neurons.end());

	auto inputRange = genome.GetInputCount() + Training::GetParameters().structure.numberOfBiasNeurons;
	NeuronRefs possibleToNeurons(neurons.begin() + inputRange, neurons.end());

	Utility::Random::Shuffle(possibleFromNeurons);
	Utility::Random::Shuffle(possibleToNeurons);


	for (auto from : possibleFromNeurons) {
		for (auto to : possibleToNeurons) {
			if (CanNeuronsBeConnected(from, to)) {
				return{ from, to };
			}
		}
	}

	throw std::runtime_error("Tried to get two unconnected Neurons while every neuron is already connected");
}

auto NeuralNetwork::CanNeuronsBeConnected(const Neuron& lhs, const Neuron& rhs) const -> bool {
	auto areNeuronsTheSame = &lhs == &rhs;
	auto canBeConnected =
	   !areNeuronsTheSame
	&& !AreBothNeuronsOutputs(lhs, rhs)
	&& !AreNeuronsConnected(lhs, rhs);

	if (!Training::GetParameters().structure.allowRecurrentConnections) {
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
	for (std::size_t i = 0; i < genome.GetGeneCount(); i++) {
		if (ShouldMutateWeight()) {
			MutateWeightOfGeneAt(i);
		}
	}
}

auto NeuralNetwork::MutateWeightOfGeneAt(std::size_t index) -> void {
	if (Utility::Random::DidChanceOccure(Training::GetParameters().mutation.chanceOfTotalWeightReset)) {
		genome[index].SetRandomWeight();
	}
	else {
		PerturbWeightAt(index);
	}
}

auto NeuralNetwork::PerturbWeightAt(std::size_t index) -> void {
	constexpr auto perturbRange = 2.5f;
	auto perturbance = Utility::Random::Number(-perturbRange, perturbRange);
	genome[index].weight += perturbance;
	const auto min = Training::GetParameters().neural.minWeight;
	const auto max = Training::GetParameters().neural.maxWeight;
	// In C++17
	// std::clamp(genome[index].weight, min, max));
	if (genome[index].weight < min) {
		genome[index].weight = min;
	}
	else if (genome[index].weight > max) {
		genome[index].weight = max;
	}
	
}

auto NeuralNetwork::MutateGenesAndBuildNetwork(Training::InnovationCacher& currGenerationInnovations) -> void {
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
	for (auto i = 0U; i < Training::GetParameters().structure.numberOfBiasNeurons; i++) {
		CategorizeNeuronBranchIntoLayers(neurons[i]);
	}
	for (auto* in : GetInputNeurons()) {
		CategorizeNeuronBranchIntoLayers(*in);
	}

	size_t highestLayer = 0U;
	auto outputNeurons = GetOutputNeurons();
	for (auto* out : outputNeurons) {
		highestLayer = std::max(out->GetLayer(), highestLayer);
	}
	for (auto* out : outputNeurons) {
		out->layer = highestLayer;
	}

	for (auto& neuron : neurons) {
		layerMap[neuron.GetLayer()].push_back(&neuron);
	}
}

auto NeuralNetwork::CategorizeNeuronBranchIntoLayers(Neuron& currNode, std::size_t currentDepth) const -> void {
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

auto NeuralNetwork::GetRandomEnabledGene() -> Genotype::Gene& {
	size_t num = Utility::Random::Number(size_t(0), genome.GetGeneCount() - size_t(1));
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
		throw std::runtime_error("Could not insert neuron because every gene is disabled");
	}
	return *randGene;
}

auto NeuralNetwork::Reset() -> void {
	for (auto& neuron : neurons) {
		neuron.Reset();
	}
}

auto NeuralNetwork::ParseNeuronsJson(const std::string& json) -> std::vector<Neuron> {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	std::size_t token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	std::vector<Neuron> neurons;

	for (std::size_t i = 0; i < token_count - 1; i++) {
		if (tokens[i].type == JSMN_OBJECT) {
			neurons.push_back(Neuron(json.substr(tokens[i].start, tokens[i].end - tokens[i].start)));
		}
	}

	return neurons;
}

std::ostream & Hippocrates::Phenotype::operator<<(std::ostream & stream, const NeuralNetwork & neuralNetwork)
{
	stream 
		<<"{\"neurons\":[";

	auto& neurons = neuralNetwork.neurons;
	const auto neuronsCount = neurons.size();

	for (std::size_t i = 0; i < neuronsCount - 1; ++i) {
		stream << neurons[i] << ",";
	}
	stream 
		<< neurons[neuronsCount - 1] <<
		"],\"genome\":{" <<
		neuralNetwork.genome <<
		"}";
	return stream;
}
