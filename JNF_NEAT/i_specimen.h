#pragma once
#include "neural_network.h"
class ISpecimen
{
	public:
		virtual ~ISpecimen() = default;

		virtual void UpdateFitness() = 0;
		virtual unsigned int GetFitness() const = 0;
		virtual const NeuralNetwork & GetNeuralNetwork() const = 0;
};