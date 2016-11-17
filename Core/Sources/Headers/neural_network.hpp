#pragma once
#include <vector>
#include <map>

#include "gene.hpp"
#include "neuron.hpp"
#include "genome.hpp"
#include "innovation_cacher.hpp"
#include "type.hpp"

namespace Hippocrates {

class NeuralNetwork {
private:
	Genome genome;
	std::vector<Neuron> neurons;
	std::map<size_t, std::vector<Neuron*>> layerMap;

public:
	NeuralNetwork(const Genome& genome);
	NeuralNetwork(Genome&& genome);
	explicit NeuralNetwork(const Genome& genome, InnovationCacher& currGenerationInnovations);
	explicit NeuralNetwork(Genome&& genome, InnovationCacher& currGenerationInnovations);
	explicit NeuralNetwork(const std::string& json);
	NeuralNetwork(const NeuralNetwork& other);
	NeuralNetwork(NeuralNetwork&& other) = default;
	virtual ~NeuralNetwork() = default;

	auto operator= (const NeuralNetwork& other) -> NeuralNetwork&;
	auto operator= (NeuralNetwork&& other) -> NeuralNetwork& = default;

	auto GetGenome() const -> const Genome&{ return genome; }
	auto GetOutputsUsingInputs(Type::neuron_values_t inputs) -> Type::neuron_values_t;
	auto GetTrainingParameters() const -> const TrainingParameters& { return GetGenome().GetTrainingParameters(); }

	auto GetJSON() const -> std::string;

	auto Reset() -> void;

private:
	auto SetInputs(Type::neuron_values_t inputs) -> void;
	auto GetOutputs() -> Type::neuron_values_t;

	auto GetOutputNeurons()->std::vector<Neuron*>;
	auto GetOutputNeurons() const ->std::vector<const Neuron*>;
	auto GetInputNeurons()->std::vector<Neuron*>;
	auto GetInputNeurons() const ->std::vector<const Neuron*>;

	auto MutateGenesAndBuildNetwork(InnovationCacher& currGenerationInnovations) -> void;
	auto BuildNetworkFromGenes() -> void;

	auto ShouldAddNeuron() const -> bool;
	auto ShouldAddConnection() const -> bool;
	auto ShouldMutateWeight() const -> bool;

	auto AddRandomNeuron(InnovationCacher& currGenerationInnovations) -> void;
	auto AddRandomConnection(InnovationCacher& currGenerationInnovations) -> void;

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
