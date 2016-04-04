#pragma once
#include "gene.h"
#include "neuron.h"
#include <vector>
class NeuralNetwork {
	private:
		std::vector<double> inputs;
		std::vector<double> outputs;
		std::vector<Gene> genes;
		std::vector<Neuron> neurons;
		bool areOutputsUpToDate = false;

	public:
		NeuralNetwork(unsigned int numberOfInputs, unsigned int numberOfOutputs);
		NeuralNetwork(std::vector<Gene> & genes);
		NeuralNetwork(const NeuralNetwork & other) = default;
		~NeuralNetwork() = default;

		void SetInputs(std::vector<double> & inputs);
		const std::vector<double> & GetOrCalculateOutputs();

		unsigned int GetNumberOfInputs() const;
		unsigned int GetNumberOfOutputs() const;
};


class invalid_inputs_exception : public std::exception
{
	using exception::exception;
};