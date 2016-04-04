#pragma once
#include "gene.h"
#include "neuron.h"
#include "sensor.h"
#include "output.h"
#include <vector>

class NeuralNetwork {
	private:
		std::vector<Gene> genes;
		std::vector<Sensor> sensors;
		std::vector<std::vector<Neuron>> hiddenLayers;
		std::vector<Output> outputNeurons;
		std::vector<double> outputs;
		bool areOutputsUpToDate = false;

	public:
		NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs);
		NeuralNetwork(const std::vector<Gene> & genes);
		NeuralNetwork(const NeuralNetwork & other) = default;
		~NeuralNetwork() = default;

		const std::vector<Gene> & GetGenes();

		void SetInputs(std::vector<double> & inputs);
		const std::vector<double> & GetOrCalculateOutputs();

	private:
		void GenerateOnlyEssentialGenes(unsigned int numberOfInputs, unsigned int numberOfOutputs);
		void BuildNetworkFromGenes();
		double GetRandomWeight() const;

		void ProcessInputLayer();
		void ProcessHiddenLayers();
		void ProcessOutputLayer();
};


class invalid_inputs_exception : public std::exception
{
	using exception::exception;
};