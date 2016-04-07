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
		std::vector<float> outputs;
		bool areOutputsUpToDate = false;

		unsigned int numberOfInputs = 0U;
		unsigned int numberOfOutputs = 0U;

	public:
		explicit NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs);
		explicit NeuralNetwork(const std::vector<Gene> & genes);
		NeuralNetwork(const NeuralNetwork & other) = default;
		~NeuralNetwork() = default;

		const std::vector<Gene> & GetGenes() const;

		void SetInputs(const std::vector<float> & inputs);
		const std::vector<float> & GetOrCalculateOutputs();

	private:
		void GenerateOnlyEssentialGenes();
		void BuildNetworkFromGenes();
		void ReadNumberOfInputsAndOutputsFromGenes();
		static float GetRandomWeight();
		void InterpretInputsAndOutputs();
		void DeleteAllNeurons() ;
};