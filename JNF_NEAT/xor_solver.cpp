#include "xor_solver.h"

void XORSolver::Reset()
{
    correctEvaluations = 0;
	currTraining = trainingData.begin();
}

void XORSolver::Update(const std::vector<float>& networkOutputs)
{    
	int xorResult = currTraining->first ^ currTraining->second;
	int networksXorResult = int(networkOutputs.front() >= 0.0f);

	if (xorResult == networksXorResult) {
        correctEvaluations++;
	}
	++currTraining;
	if (currTraining == trainingData.end()) {
		currTraining = trainingData.begin();
	}
}

double XORSolver::GetFitness() const
{
	return double(correctEvaluations * correctEvaluations);
}

std::vector<float> XORSolver::ProvideNetworkWithInputs() const
{
	std::vector<float> inputs = {(float)currTraining->first, (float)currTraining->second};
	return inputs;
}