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
		std::vector<std::pair<int,int>> trainingData = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
		std::vector<std::pair<int,int>>::iterator currTraining = trainingData.begin();
};