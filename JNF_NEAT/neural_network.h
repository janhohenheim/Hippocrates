#pragma once
#include "gene.h"
#include "neuron.h"
#include "genome.h"
#include <vector>
#include <map>

namespace JNF_NEAT {

	class NeuralNetwork {
		private:
			Genome genome;
			std::vector<Neuron> neurons;
			std::vector<Neuron*> inputNeurons;
			std::vector<Neuron*> outputNeurons;
			const TrainingParameters& parameters;
			std::map<size_t, std::vector<Neuron*>> layerMap;

		public:
			NeuralNetwork() = delete;
			explicit NeuralNetwork(const TrainingParameters& parameters, bool shouldMutate = false);
			explicit NeuralNetwork(const Genome& genome, bool shouldMutate = false);
			explicit NeuralNetwork(Genome&& genome, bool shouldMutate = false);
			NeuralNetwork(const NeuralNetwork& other);
			NeuralNetwork(NeuralNetwork&& other) = default;
			~NeuralNetwork() = default;
			NeuralNetwork& operator= (const NeuralNetwork& other);
			NeuralNetwork& operator= (NeuralNetwork&& other) = default;

			const Genome& GetGenome() const { return genome; }
			std::vector<float> GetOutputsUsingInputs(std::vector<float> inputs);
			const TrainingParameters& GetTrainingParameters() const { return parameters; }
			std::string GetJSON() const;
		private:
			void SetInputs(std::vector<float> inputs);
			std::vector<float> GetOutputs();
			void MutateGenesAndBuildNetwork();
			static bool DidChanceOccure(float chance);
			void BuildNetworkFromGenes();
			void InterpretInputsAndOutputs();
			bool ShouldAddNeuron() const { return DidChanceOccure(parameters.advanced.mutation.chanceForNeuralMutation); }
			bool ShouldAddConnection() const;
			bool ShouldMutateWeight() const { return DidChanceOccure(parameters.advanced.mutation.chanceForWeightMutation); }
			void AddRandomNeuron();
			void AddRandomConnection();
			std::pair<Neuron*, Neuron*> GetTwoUnconnectedNeurons();
			bool CanNeuronsBeConnected(const Neuron& lhs, const Neuron& rhs) const;
			bool AreBothNeuronsOutputs(const Neuron& lhs, const Neuron& rhs) const;
			bool AreNeuronsConnected(const Neuron& lhs, const Neuron& rhs) const;
			void ShuffleWeights();
			void MutateWeightOfGeneAt(std::size_t index);
			void PerturbWeightAt(std::size_t index);
			void CategorizeNeuronsIntoLayers();
			void CategorizeNeuronBranchIntoLayers(Neuron& currNode, size_t currentDepth = 0);
			Gene& GetRandomEnabledGene();
	};

}