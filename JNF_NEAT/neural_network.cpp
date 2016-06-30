#include "neural_network.h"
#include <algorithm>

using namespace JNF_NEAT;
using namespace std;

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

NeuralNetwork::NeuralNetwork(const Genome& genome, bool shouldMutate):
	parameters(genome.GetTrainingParameters()),
	genome(genome),
	inputNeurons(genome.GetTrainingParameters().numberOfInputs),
	outputNeurons(genome.GetTrainingParameters().numberOfOutputs)
{
	if (shouldMutate) {
		MutateGenesAndBuildNetwork();
	} else {
		BuildNetworkFromGenes();
	}
}

NeuralNetwork::NeuralNetwork(Genome&& genome, bool shouldMutate) :
	parameters(genome.GetTrainingParameters()),
	genome(move(genome)),
	inputNeurons(genome.GetTrainingParameters().numberOfInputs),
	outputNeurons(genome.GetTrainingParameters().numberOfOutputs)
{
	if (shouldMutate) {
		MutateGenesAndBuildNetwork();
	}
	else {
		BuildNetworkFromGenes();
	}
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& other) :
	parameters(other.parameters),
	genome(other.genome),
	neurons(other.neurons.size()),
	inputNeurons(other.inputNeurons.size()),
	outputNeurons(other.outputNeurons.size()),
	layerMap(other.layerMap)
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

void NeuralNetwork::SetInputs(vector<float> inputs) {
	if (inputNeurons.size() != inputs.size()) {
		throw out_of_range("Number of inputs provided doesn't match genetic information");
	}
	for(size_t i = 0U; i < inputNeurons.size(); ++i) {
		inputNeurons[i]->SetInput(move(inputs[i]));
	};
}

vector<float> NeuralNetwork::GetOutputs() {
	for (size_t i = 1; i < layerMap.size() - 1; ++i) {
		for (auto& neuron : layerMap[i]){
			neuron->RequestDataAndGetActionPotential();
		}
	}
	vector<float> outputs;
	outputs.reserve(outputNeurons.size());
	for(auto& outputNeuron : outputNeurons) {
		outputs.push_back(outputNeuron->RequestDataAndGetActionPotential());
	}
	return outputs;
}

vector<float> NeuralNetwork::GetOutputsUsingInputs(vector<float> inputs) {
	SetInputs(move(inputs));
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
		outputNeurons[i] = &neurons[genome[i].to];
	}
}

bool NeuralNetwork::ShouldAddConnection() const {
	const bool hasChanceOccured = DidChanceOccure(parameters.advanced.mutation.chanceForConnectionalMutation);
	if (!hasChanceOccured) {
		return false;
	}
	const size_t inputLayerSize = parameters.numberOfInputs + parameters.advanced.structure.numberOfBiasNeurons;
	const size_t outputLayerSize = parameters.numberOfOutputs;
	const size_t hiddenLayerSize = genome.GetNeuronCount() - inputLayerSize - outputLayerSize;
	size_t numberOfPossibleConnections = hiddenLayerSize * (hiddenLayerSize - 1);
	numberOfPossibleConnections += hiddenLayerSize * inputLayerSize;
	numberOfPossibleConnections += hiddenLayerSize * outputLayerSize;

	const size_t generatedNeurons = genome.GetNeuronCount() - (inputLayerSize + parameters.numberOfOutputs);
	const bool hasSpaceForNewConnections = genome.GetGeneCount() < (numberOfPossibleConnections + generatedNeurons);
	return hasSpaceForNewConnections;
}

bool NeuralNetwork::DidChanceOccure(float chance) {
	auto num = rand() % 100;
	return num < int(100.0f * chance);
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

	genome.AppendGene(move(g1));
	genome.AppendGene(move(g2));
}

void NeuralNetwork::AddRandomConnection() {
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

pair<Neuron*, Neuron*> NeuralNetwork::GetTwoUnconnectedNeurons() {
	vector<Neuron*> possibleFromNeurons;
	possibleFromNeurons.reserve(neurons.size());
	for (auto& n : neurons) {
		possibleFromNeurons.push_back(&n);
	}
	auto inputRange = parameters.numberOfInputs + parameters.advanced.structure.numberOfBiasNeurons;
	vector<Neuron*> possibleToNeurons(possibleFromNeurons.begin() + inputRange, possibleFromNeurons.end());

	random_shuffle(possibleFromNeurons.begin(), possibleFromNeurons.end());
	random_shuffle(possibleToNeurons.begin(), possibleToNeurons.end());


	for (auto* from : possibleFromNeurons) {
		for (auto* to : possibleToNeurons) {
			if (CanNeuronsBeConnected(*from, *to)) {
				return {from, to};
			}
		}
	}

	throw runtime_error("Tried to get two unconnected Neurons while every neuron is already connected");
}

bool JNF_NEAT::NeuralNetwork::CanNeuronsBeConnected(const Neuron & lhs, const Neuron & rhs) const {
	bool AreNeuronsTheSame = &lhs == &rhs;
	return (!AreNeuronsTheSame && !AreBothNeuronsOutputs(lhs, rhs) && !AreNeuronsConnected(lhs, rhs));
}

bool NeuralNetwork::AreBothNeuronsOutputs(const Neuron &lhs, const Neuron &rhs) const {
	bool isLhsOutput = false;
	bool isRhsOutput = false;
	for (const auto& output: outputNeurons){
		if (output == &lhs){
			isLhsOutput = true;
		}
		else if (output == &rhs){
			isRhsOutput = true;
		}
		if (isLhsOutput && isRhsOutput){
			return true;
		}
	}
	return false;
}

bool NeuralNetwork::AreNeuronsConnected(const Neuron& lhs,const Neuron & rhs) const {
	for (auto& connection : rhs.GetConnections()) {
		if (!connection.outGoing && &lhs == connection.neuron) {
			return true;
		}
	}
	return false;
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
	for (auto i = 0U; i < parameters.advanced.structure.numberOfBiasNeurons; i++) {
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

void NeuralNetwork::CategorizeNeuronBranchIntoLayers(Neuron& currNode, size_t currentDepth) {
	currNode.layer = currentDepth;
	const size_t nextLayer = currNode.layer + 1;


	auto HasYetToBeLayered = [&nextLayer](const Neuron::Connection& c) {
		return nextLayer > c.neuron->layer;
	};
	auto IsInHigherLayer = [](const Neuron::Connection& c) {
		return (c.outGoing != c.isRecursive);
	};

	for (auto &c : currNode.GetConnections()) {
		if (HasYetToBeLayered(c) && IsInHigherLayer(c)) {
			CategorizeNeuronBranchIntoLayers(*c.neuron, nextLayer);
		}
	}
}

Gene& NeuralNetwork::GetRandomEnabledGene() {
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

string NeuralNetwork::GetJSON() const{
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