#pragma once
#include "body.h"
class XORSolver : public IBody {
	public:
		virtual void Reset() override;
		virtual void Update(const std::vector<float>& networkOutputs) override;
		virtual double GetFitness() const override;

		virtual std::vector<float> ProvideNetworkWithInputs() const override;

	private:
		std::vector<std::pair<int,int>> trainingData = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
		std::vector<int> results;
		std::vector<std::pair<int,int>>::iterator currTraining = trainingData.begin();
};