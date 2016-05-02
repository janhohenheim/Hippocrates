#include "xor_solver.h"

void XORSolver::Reset()
{
	fitness = 0;
	currTraining = trainingData.begin();
}

void XORSolver::Update(const std::vector<float>&  networkOutputs)
{
	int xorResult = currTraining->first ^ currTraining->second;
	int networksXorResult = int(networkOutputs[0] > 0.5f);

	if (xorResult == networksXorResult) {
		fitness += 10;
	}
}

int XORSolver::GetOrCalculateFitness()
{
	return fitness;
}

std::vector<float> XORSolver::ProvideNetworkWithInputs()
{
	std::vector<float> inputs = {(float)currTraining->first, (float)currTraining->second};
	++currTraining;
	return inputs;
}
