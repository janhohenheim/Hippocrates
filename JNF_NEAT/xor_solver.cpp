#include "xor_solver.h"

void XORSolver::Reset()
{
	fitness = 0;
}

void XORSolver::Update()
{
}

int XORSolver::GetOrCalculateFitness()
{
	return fitness;
}

void XORSolver::ReceiveNetworkOutputs(std::vector<float> outputs)
{
	int xorResult = (int)lastInputs[0] ^ (int)lastInputs[1];

	std::vector<int> outputsAsInts = { 0, 0 };
	if (outputs[0] > 0.5f) {
		outputsAsInts[0] = 1;
	}
	if (outputs[1] > 0.5f) {
		outputsAsInts[1] = 1;
	}

	int networksXorResult = outputsAsInts[0] ^ outputsAsInts[1];

	if (xorResult == networksXorResult) {
		fitness += 10;
	}
}

std::vector<float> XORSolver::ProvideNetworkWithInputs()
{
	lastInputs.clear();
	lastInputs.push_back(float(rand() % 2));
	lastInputs.push_back(float(rand() % 2));

	return lastInputs;
}
