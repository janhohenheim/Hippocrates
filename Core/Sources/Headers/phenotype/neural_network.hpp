#pragma once
#include <vector>
#include <map>

#include "neuron.hpp"
#include "genotype/genome.hpp"
#include "training/innovation_cacher.hpp"
#include "type.hpp"

namespace Hippocrates::Phenotype {

class NeuralNetwork {
private:
	Genotype::Genome genome;
	std::vector<Neuron> neurons;
	std::map<size_t, std::vector<Neuron*>> layerMap;

public:
	explicit NeuralNetwork(const Genotype::Genome& genome);
	explicit NeuralNetwork(Genotype::Genome&& genome);
	explicit NeuralNetwork(const Genotype::Genome& genome, Training::InnovationCacher& currGenerationInnovations);
	explicit NeuralNetwork(Genotype::Genome&& genome, Training::InnovationCacher& currGenerationInnovations);
	explicit NeuralNetwork(const std::string& json);
	NeuralNetwork(const NeuralNetwork& other);
	NeuralNetwork(NeuralNetwork&& other) = default;
	virtual ~NeuralNetwork() = default;

	auto operator= (const NeuralNetwork& other)&-> NeuralNetwork&;
	auto operator= (NeuralNetwork&& other)&-> NeuralNetwork& = default;

	auto GetGenome() const -> const Genotype::Genome&{ return genome; }
	auto GetOutputsUsingInputs(Type::neuron_values_t inputs) -> Type::neuron_values_t;

	friend std::ostream& operator<<(std::ostream& stream, const NeuralNetwork & neuralNetwork);

	auto Reset() -> void;

private:
	auto SetInputs(Type::neuron_values_t inputs) -> void;
	auto GetOutputs() -> Type::neuron_values_t;

	auto GetOutputNeurons()->std::vector<Neuron*>;
	auto GetOutputNeurons() const ->std::vector<const Neuron*>;
	auto GetInputNeurons()->std::vector<Neuron*>;
	auto GetInputNeurons() const ->std::vector<const Neuron*>;

	auto MutateGenesAndBuildNetwork(Training::InnovationCacher& currGenerationInnovations) -> void;
	auto BuildNetworkFromGenes() -> void;

	auto ShouldAddNeuron() const -> bool;
	auto ShouldAddConnection() const -> bool;
	auto ShouldMutateWeight() const -> bool;

	auto AddRandomNeuron(Training::InnovationCacher& currGenerationInnovations) -> void;
	auto AddRandomConnection(Training::InnovationCacher& currGenerationInnovations) -> void;

	auto GetTwoUnconnectedNeurons() -> std::pair<Neuron&, Neuron&>;
	auto GetRandomEnabledGene() -> Genotype::Gene&;

	auto CanNeuronsBeConnected(const Neuron& lhs, const Neuron& rhs) const -> bool;
	auto AreBothNeuronsOutputs(const Neuron& lhs, const Neuron& rhs) const -> bool;
	static auto AreNeuronsConnected(const Neuron& lhs, const Neuron& rhs) -> bool;

	auto ShuffleWeights() -> void;
	auto MutateWeightOfGeneAt(std::size_t index) -> void;
	auto PerturbWeightAt(std::size_t index) -> void;

	auto CategorizeNeuronsIntoLayers() -> void;
	auto CategorizeNeuronBranchIntoLayers(Neuron& currNode, std::size_t currentDepth = 0) const -> void;

	auto ParseNeuronsJson(const std::string& json) -> std::vector<Neuron>;


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
