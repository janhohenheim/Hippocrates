#include <algorithm>
#include "../Headers/neural_network.h"

using namespace Hippocrates;
using namespace std;

NeuralNetwork::NeuralNetwork(const Genome& genome, bool shouldMutate) :
	genome(genome),
	inputNeurons(genome.GetInputCount()),
	outputNeurons(genome.GetOutputCount())
{
	if (shouldMutate) {
		MutateGenesAndBuildNetwork();
	}
	else {
		BuildNetworkFromGenes();
	}
}

NeuralNetwork::NeuralNetwork(Genome&& genome, bool shouldMutate) :
	genome(move(genome)),
	inputNeurons(genome.GetInputCount()),
	outputNeurons(genome.GetOutputCount())
{
	if (shouldMutate) {
		MutateGenesAndBuildNetwork();
	}
	else {
		BuildNetworkFromGenes();
	}
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& other) :
	genome(other.genome),
	inputNeurons(other.inputNeurons.size()),
	outputNeurons(other.outputNeurons.size())
{
	BuildNetworkFromGenes();
}

auto NeuralNetwork::operator=(const NeuralNetwork& other) -> NeuralNetwork& {
	genome = other.genome;
	inputNeurons.resize(other.inputNeurons.size());
	outputNeurons.resize(other.outputNeurons.size());
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
	InterpretInputsAndOutputs();
	CategorizeNeuronsIntoLayers();
}

auto NeuralNetwork::SetInputs(vector<float> inputs) -> void {
	if (inputNeurons.size() != inputs.size()) {
		throw out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for (size_t i = 0U; i < inputNeurons.size(); ++i) {
		inputNeurons[i]->SetInput(move(inputs[i]));
	};
}

auto NeuralNetwork::GetOutputs() -> vector<float> {
	for (size_t i = 1; i < layerMap.size() - 1; ++i) {
		for (auto& neuron : layerMap[i]) {
			neuron->RequestDataAndGetActionPotential();
		}
	}
	vector<float> outputs;
	outputs.reserve(outputNeurons.size());
	for (auto& outputNeuron : outputNeurons) {
		outputs.push_back(outputNeuron->RequestDataAndGetActionPotential());
	}
	return outputs;
}

auto NeuralNetwork::GetOutputsUsingInputs(vector<float> inputs) -> vector<float> {
	SetInputs(move(inputs));
	return GetOutputs();
}

auto NeuralNetwork::InterpretInputsAndOutputs() -> void {
	// Bias
	for (auto i = 0U; i < GetTrainingParameters().structure.numberOfBiasNeurons; i++) {
		neurons[i].SetInput(1.0f);
	}

	// Inputs
	for (auto i = 0U; i < genome.GetInputCount(); i++) {
		inputNeurons[i] = &neurons[i + GetTrainingParameters().structure.numberOfBiasNeurons];
	}

	// Outputs
	for (auto i = 0U; i < genome.GetOutputCount(); i++) {
		outputNeurons[i] = &neurons[genome[i].to];
	}
}

auto NeuralNetwork::ShouldAddNeuron() const -> bool {
	return DidChanceOccure(
		GetTrainingParameters().
		
		mutation.
		chanceForNeuralMutation
	);
}

auto NeuralNetwork::ShouldAddConnection() const -> bool {
	const bool hasChanceOccured = DidChanceOccure(GetTrainingParameters().mutation.chanceForConnectionalMutation);
	if (!hasChanceOccured) {
		return false;
	}
	const size_t inputLayerSize = genome.GetInputCount() + GetTrainingParameters().structure.numberOfBiasNeurons;
	const size_t outputLayerSize = genome.GetOutputCount();
	const size_t hiddenLayerSize = genome.GetNeuronCount() - inputLayerSize - outputLayerSize;

	
	const auto startingConnections = inputLayerSize * outputLayerSize;
	auto hiddenConnections = (hiddenLayerSize * (hiddenLayerSize - 1));
	if (!GetTrainingParameters().structure.allowRecursiveConnections) {
		hiddenConnections /= 2;
	}
	const auto connectionsFromInputs = inputLayerSize * hiddenLayerSize;
	auto connectionsToOutputs = outputLayerSize * hiddenLayerSize;
	if (GetTrainingParameters().structure.allowRecursiveConnections) {
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
	return DidChanceOccure(
		GetTrainingParameters().		
		mutation.
		chanceForWeightMutation
	);
}

auto NeuralNetwork::DidChanceOccure(float chance) -> bool {
	auto num = rand() % 100;
	return num < int(100.0f * chance);
}

auto NeuralNetwork::AddRandomNeuron() -> void {
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

	genome.AppendGene(move(g1));
	genome.AppendGene(move(g2));
}

auto NeuralNetwork::AddRandomConnection() -> void {
	// Data
	auto NeuronPair(GetTwoUnconnectedNeurons());
	auto& fromNeuron = *NeuronPair.first;
	auto& toNeuron = *NeuronPair.second;

	// Gene
	Gene newConnectionGene;
	while (&neurons[newConnectionGene.from] != &fromNeuron) {
		newConnectionGene.from++;
	}
	while (&neurons[newConnectionGene.to] != &toNeuron) {
		newConnectionGene.to++;
	}
	if (fromNeuron.GetLayer() > toNeuron.GetLayer()) {
		newConnectionGene.isRecursive = true;
	}

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

auto NeuralNetwork::GetTwoUnconnectedNeurons() -> pair<Neuron*, Neuron*> {
	vector<Neuron*> possibleFromNeurons;
	possibleFromNeurons.reserve(neurons.size());
	for (auto& n : neurons) {
		possibleFromNeurons.push_back(&n);
	}
	auto inputRange = genome.GetInputCount() + GetTrainingParameters().structure.numberOfBiasNeurons;
	vector<Neuron*> possibleToNeurons(possibleFromNeurons.begin() + inputRange, possibleFromNeurons.end());

	random_shuffle(possibleFromNeurons.begin(), possibleFromNeurons.end());
	random_shuffle(possibleToNeurons.begin(), possibleToNeurons.end());


	for (auto* from : possibleFromNeurons) {
		for (auto* to : possibleToNeurons) {
			if (CanNeuronsBeConnected(*from, *to)) {
				return{ from, to };
			}
		}
	}

	throw runtime_error("Tried to get two unconnected Neurons while every neuron is already connected");
}

auto Hippocrates::NeuralNetwork::CanNeuronsBeConnected(const Neuron & lhs, const Neuron & rhs) const -> bool {
	bool AreNeuronsTheSame = &lhs == &rhs;
	return (!AreNeuronsTheSame && !AreBothNeuronsOutputs(lhs, rhs) && !AreNeuronsConnected(lhs, rhs));
}

auto NeuralNetwork::AreBothNeuronsOutputs(const Neuron &lhs, const Neuron &rhs) const -> bool {
	bool isLhsOutput = false;
	bool isRhsOutput = false;
	for (const auto& output : outputNeurons) {
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
	if (DidChanceOccure(GetTrainingParameters().mutation.chanceOfTotalWeightReset)) {
		genome[index].SetRandomWeight();
	}
	else {
		PerturbWeightAt(index);
	}
}

auto NeuralNetwork::PerturbWeightAt(size_t index) -> void {
	constexpr float perturbanceBoundaries = 0.5f;
	auto perturbance = static_cast<float>(rand() % 10'000) / 9'999.0f * perturbanceBoundaries;
	if (rand() % 2) {
		perturbance = -perturbance;
	}
	genome[index].weight += perturbance;
	if (genome[index].weight < -1.0f) {
		genome[index].weight = -1.0f;
	}
	else if (genome[index].weight > 1.0f) {
		genome[index].weight = 1.0f;
	}
}

auto NeuralNetwork::MutateGenesAndBuildNetwork() -> void {
	if (ShouldAddConnection()) {
		BuildNetworkFromGenes();
		AddRandomConnection();
	}
	else {
		if (ShouldAddNeuron()) {
			AddRandomNeuron();
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
	for (auto* in : inputNeurons) {
		CategorizeNeuronBranchIntoLayers(*in);
	}

	size_t highestLayer = 0U;
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
	size_t num = rand() % genome.GetGeneCount();
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
	for (size_t i = 0; i < neurons.size() - 1; ++i) {
		s += neurons[i].GetJSON();
		s += ",";
	}
	s += neurons.back().GetJSON();
	s += "],\"genome\":";
	s += genome.GetJSON();
	s += "}";
	return s;
}
