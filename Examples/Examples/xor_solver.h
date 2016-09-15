#pragma once
#include "../../Library/JNF_NEAT/body.h"
class XORSolver : public JNF_NEAT::IBody {
public:
	auto Reset() -> void override;
	auto Update(const std::vector<float>& networkOutputs) -> void override;
	auto GetFitness() const -> double override;

	auto HasFinishedTask() const -> bool override;
	auto ProvideNetworkWithInputs() const -> std::vector<float> override;

	auto GetInputCount() const -> std::size_t override { return 2; };
	auto GetOutputCount() const -> std::size_t override { return 1; };
private:
	std::vector<std::pair<int, int>> trainingData = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
	std::vector<int> results;
	std::vector<std::pair<int, int>>::iterator currTraining = trainingData.begin();
};
