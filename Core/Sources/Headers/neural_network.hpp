#pragma once
#include "gene.hpp"
#include "neuron.hpp"
#include "genome.hpp"
#include <vector>
#include <map>

namespace Hippocrates {

class NeuralNetwork {
private:
	Genome genome;
	std::vector<Neuron> neurons;
	std::map<size_t, std::vector<Neuron*>> layerMap;

public:
	explicit NeuralNetwork(const Genome& genome, bool shouldMutate = false);
	explicit NeuralNetwork(Genome&& genome, bool shouldMutate = false);
	explicit NeuralNetwork(const std::string& json);
	NeuralNetwork(const NeuralNetwork& other);
	NeuralNetwork(NeuralNetwork&& other) = default;
	~NeuralNetwork() = default;

	auto operator= (const NeuralNetwork& other) -> NeuralNetwork&;
	auto operator= (NeuralNetwork&& other) -> NeuralNetwork& = default;

	auto GetGenome() const -> const Genome&{ return genome; }
	auto GetOutputsUsingInputs(std::vector<float> inputs) -> std::vector<float>;
	auto GetTrainingParameters() const -> const TrainingParameters& { return GetGenome().GetTrainingParameters(); }

	auto GetJSON() const -> std::string;

	auto Reset() -> void;

private:
	auto SetInputs(std::vector<float> inputs) -> void;
	auto GetOutputs() -> std::vector<float>;

	auto GetOutputNeurons()->std::vector<Neuron*>;
	auto GetOutputNeurons() const ->std::vector<const Neuron*>;
	auto GetInputNeurons()->std::vector<Neuron*>;
	auto GetInputNeurons() const ->std::vector<const Neuron*>;

	auto MutateGenesAndBuildNetwork() -> void;
	auto BuildNetworkFromGenes() -> void;

	auto ShouldAddNeuron() const -> bool;
	auto ShouldAddConnection() const -> bool;
	auto ShouldMutateWeight() const -> bool;

	auto AddRandomNeuron() -> void;
	auto AddRandomConnection() -> void;

	auto GetTwoUnconnectedNeurons() -> std::pair<Neuron&, Neuron&>;
	auto GetRandomEnabledGene() -> Gene&;

	auto CanNeuronsBeConnected(const Neuron& lhs, const Neuron& rhs) const -> bool;
	auto AreBothNeuronsOutputs(const Neuron& lhs, const Neuron& rhs) const -> bool;
	static auto AreNeuronsConnected(const Neuron& lhs, const Neuron& rhs) -> bool;

	auto ShuffleWeights() -> void;
	auto MutateWeightOfGeneAt(std::size_t index) -> void;
	auto PerturbWeightAt(std::size_t index) -> void;

	auto CategorizeNeuronsIntoLayers() -> void;
	auto CategorizeNeuronBranchIntoLayers(Neuron& currNode, size_t currentDepth = 0) const -> void;

	auto ParseNeuronsJson(std::string json) -> std::vector<Neuron>;


	template<typename Lambda>
	auto GetNeuronsByRangeAndIndex(std::size_t range, Lambda&& index) {
		std::vector<Neuron*> neuronsInRange;
		neuronsInRange.reserve(range);

		for (auto i = 0U; i < range; i++) {
			neuronsInRange.push_back(&neurons[index(i)]);
		}
		return neuronsInRange;
	}

	template<typename Lambda>
	auto GetNeuronsByRangeAndIndex(std::size_t range, Lambda&& index) const	{
		std::vector<const Neuron*> neuronsInRange;
		neuronsInRange.reserve(range);

		for (auto i = 0U; i < range; i++) {
			neuronsInRange.push_back(&neurons[index(i)]);
		}
		return neuronsInRange;
	}
};

}
