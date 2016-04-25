#pragma once
#include "trainable.h"
class XORSolver : public ITrainable {
	public:
		virtual void Reset() override;
		virtual void Update(const std::vector<float>&  networkOutputs) override;
		virtual int GetOrCalculateFitness() override;

		virtual std::vector<float> ProvideNetworkWithInputs() override;
	private:
		int fitness = 0;
		std::vector<float> lastInputs;
};