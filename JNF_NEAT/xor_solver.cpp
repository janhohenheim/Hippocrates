#include "xor_solver.h"
#include <stdlib.h>

void XORSolver::Reset()
{
	fitness = 0;
}

void XORSolver::Update(const std::vector<float>&  networkOutputs)
{
	int xorResult = (int)lastInputs[0] ^ (int)lastInputs[1];
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
	lastInputs.clear();
	lastInputs.push_back(float(rand() % 2));
	lastInputs.push_back(float(rand() % 2));

	return lastInputs;
}
