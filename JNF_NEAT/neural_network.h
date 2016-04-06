#pragma once
#include "gene.h"
#include "neuron.h"
#include "sensor.h"
#include <vector>

class NeuralNetwork {
	private:
		std::vector<Gene> genes;
		std::vector<Sensor> sensors;
		std::vector<std::vector<Neuron>> hiddenLayers;
		std::vector<Neuron *> outputNeurons;
		std::vector<float> outputs;
		bool areOutputsUpToDate = false;

	public:
		NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs);
		NeuralNetwork(const std::vector<Gene> & genes);
		NeuralNetwork(const NeuralNetwork & other) = default;
		~NeuralNetwork() = default;

		const std::vector<Gene> & GetGenes() const;

		void SetInputs(std::vector<float> & inputs);
		const std::vector<float> & GetOrCalculateOutputs();

	private:
		void GenerateOnlyEssentialGenes(unsigned int numberOfInputs, unsigned int numberOfOutputs);
		void BuildNetworkFromGenes();
		float GetRandomWeight() const;
		void InterpretOutputNeurons();
		void DeleteAllNeurons() ;
};