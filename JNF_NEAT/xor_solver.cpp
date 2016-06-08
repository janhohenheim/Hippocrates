#include "xor_solver.h"

void XORSolver::Reset()
{
	currTraining = trainingData.begin();
	results.clear();
}

void XORSolver::Update(const std::vector<float>& networkOutputs)
{    
	int xorResult = currTraining->first ^ currTraining->second;
	int networksXorResult = int(networkOutputs.front() >= 0.0f);

	results.push_back(networksXorResult);
	++currTraining;
	if (currTraining == trainingData.end()) {
		currTraining = trainingData.begin();
	}
}

double XORSolver::GetFitness() const
{
	size_t correctEvaluations = 0;
	auto firstResult = results.front();
	bool areAllResultsSame = true;
	for (size_t i = 0; i < trainingData.size(); ++i) {
		auto correctResult = trainingData[i].first ^ trainingData[i].second;
		if (results[i] == correctResult) {
			correctEvaluations++;
		}
		if (results[i] != firstResult) {
			areAllResultsSame = false;
		}
	}
	if (areAllResultsSame) {
		return 0.0;
	}
	return double(correctEvaluations * correctEvaluations);
}

std::vector<float> XORSolver::ProvideNetworkWithInputs() const
{
	std::vector<float> inputs = {(float)currTraining->first, (float)currTraining->second};
	return inputs;
}