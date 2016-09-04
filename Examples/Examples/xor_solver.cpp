#include "xor_solver.h"

auto XORSolver::Reset() -> void {
	currTraining = trainingData.begin();
	results.clear();
}

auto XORSolver::Update(const std::vector<float>& networkOutputs) -> void {    
	int xorResult = currTraining->first ^ currTraining->second;
	int networksXorResult = int(networkOutputs.front() >= 0.0f);

	results.push_back(networksXorResult);
	++currTraining;
}

auto XORSolver::GetFitness() const -> double {
	std::size_t correctEvaluations = 0;
	auto firstResult = results.front();
	bool areAllResultsSame = true;
	for (std::size_t i = 0; i < trainingData.size(); ++i) {
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

auto XORSolver::ProvideNetworkWithInputs() const -> std::vector<float> {
	std::vector<float> inputs = {(float)currTraining->first, (float)currTraining->second};
	return inputs;
}

auto XORSolver::HasFinishedTask() const -> bool {
	return currTraining == trainingData.end();
}
