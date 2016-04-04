#pragma once
#include "neural_network.h"

class ISpecimen
{
	public:
		virtual ~ISpecimen() = default;

		virtual void Update() = 0;
		virtual void RecalculateFitness() = 0;
		virtual unsigned int GetFitness() const = 0;
		virtual const NeuralNetwork & GetNeuralNetwork() const = 0;
};