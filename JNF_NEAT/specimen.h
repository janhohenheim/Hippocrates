#pragma once
#include "neural_network.h"
class ISpecimen
{
	public:
		virtual ~ISpecimen() = default;
		virtual void UpdateFitness() abstract;
		virtual unsigned int GetFitness() const abstract;
		virtual const NeuralNetwork & GetNeuralNetwork() const abstract;
};