#pragma once
#include "gene.h"
#include "neuron.h"
#include <vector>

class NeuralNetwork {
	private:
		std::vector<Gene> genes;
		std::vector<Neuron> neurons;
		std::vector<Neuron *> inputNeurons;
		std::vector<Neuron *> outputNeurons;

	public:
		explicit NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs);
        explicit NeuralNetwork(const std::vector<Gene> & genes);
        explicit NeuralNetwork(std::vector<Gene> && genes);
        NeuralNetwork(const std::vector<Gene> && genes) = delete;

		NeuralNetwork(const NeuralNetwork & other);
		NeuralNetwork(NeuralNetwork && other);

		~NeuralNetwork() = default;

		NeuralNetwork & operator= (const NeuralNetwork & other);

		const std::vector<Gene> & GetGenes() const;

		void SetInputs(const std::vector<float> & inputs);
		std::vector<float> GetOutputs();

	private:
		void GenerateOnlyEssentialGenes();
		void ReadNumberOfInputsAndOutputsFromGenes();
		void BuildNetworkFromGenes();
		void InterpretInputsAndOutputs();
		void DeleteAllNeurons();
};