#pragma once
#include "../../JNF_NEAT/body.h"
class XORSolver : public JNF_NEAT::IBody {
public:
	virtual auto Reset() -> void override;
	virtual auto Update(const std::vector<float>& networkOutputs) -> void override;
	virtual auto GetFitness() const -> double override;

	virtual auto HasFinishedTask() const -> bool override;
	virtual auto ProvideNetworkWithInputs() const -> std::vector<float> override;

private:
	std::vector<std::pair<int, int>> trainingData = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
	std::vector<int> results;
	std::vector<std::pair<int, int>>::iterator currTraining = trainingData.begin();
};
