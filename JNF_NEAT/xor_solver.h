#pragma once
#include "trainable.h"
class XORSolver : public ITrainable {
	public:
		virtual void Reset();
		virtual void Update();
		virtual int GetOrCalculateFitness();

		virtual void ReceiveNetworkOutputs(std::vector<float> outputs);
		virtual std::vector<float> ProvideNetworkWithInputs();
	private:
		int fitness = 0;
		std::vector<float> lastInputs;
};