#pragma once
#include "gene.h"
#include "neuron.h"
#include "genome.h"
#include <vector>

class NeuralNetwork {
	private:
		Genome genome;
		std::vector<Neuron> neurons;
		std::vector<Neuron*> inputNeurons;
		std::vector<Neuron*> outputNeurons;

	public:
		explicit NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs);
        explicit NeuralNetwork(const Genome& genome);
        explicit NeuralNetwork(Genome&& genome);
        NeuralNetwork(const Genome&& genome) = delete;

		NeuralNetwork(const NeuralNetwork& other);
		NeuralNetwork(NeuralNetwork&& other);

		~NeuralNetwork() = default;

		NeuralNetwork& operator= (const NeuralNetwork& other);

		const Genome& GetGenome() const { return genome; }

		void SetInputs(const std::vector<float>& inputs);
		std::vector<float> GetOutputs();

	private:
		void GenerateOnlyEssentialGenes();
		void ReadNumberOfInputsAndOutputsFromGenes();
		void BuildNetworkFromGenes();
		void InterpretInputsAndOutputs();
		void DeleteAllNeurons();
};