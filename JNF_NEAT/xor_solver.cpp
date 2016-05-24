#include "xor_solver.h"

void XORSolver::Reset()
{
	fitness = 0;
	currTraining = trainingData.begin();
}

void XORSolver::Update(const std::vector<float>&  networkOutputs)
{    
	int xorResult = currTraining->first ^ currTraining->second;
	int networksXorResult = int(networkOutputs.front() >= 0.5f);

	if (xorResult == networksXorResult) {
		fitness += 10;
	}
    ++currTraining;
    if (currTraining == trainingData.end()) {
        currTraining = trainingData.begin();
    }
}

int XORSolver::GetFitness() const
{
	return fitness;
}

std::vector<float> XORSolver::ProvideNetworkWithInputs() const
{
	std::vector<float> inputs = {(float)currTraining->first, (float)currTraining->second};
	return inputs;
}