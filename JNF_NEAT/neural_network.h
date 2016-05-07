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
		const TrainingParameters& parameters;

	public:
        NeuralNetwork() = delete;
		explicit NeuralNetwork(const TrainingParameters & parameters);
        explicit NeuralNetwork(const Genome& genome);
        explicit NeuralNetwork(Genome&& genome);
        explicit NeuralNetwork(const Genome&& genome) = delete;

		NeuralNetwork(const NeuralNetwork& other);
		NeuralNetwork(NeuralNetwork&& other);

		~NeuralNetwork() = default;


		NeuralNetwork& operator= (const NeuralNetwork& other);

		const Genome& GetGenome() const { return genome; }

		void SetInputs(const std::vector<float>& inputs);
		std::vector<float> GetOutputs();

	private:
		void BuildNetworkFromGenes();
		void InterpretInputsAndOutputs();
};