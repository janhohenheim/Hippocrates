#include "testing_utilities.hpp"

using namespace std;
using namespace Hippocrates;

enum class XORResult {
	Zero,
	One,
	ClassificationCount
};

int main() {
	TrainingData<std::vector<float>, XORResult> data;
	data.AddSet({ {0.0f, 0.0f}, XORResult::Zero });
	data.AddSet({ {0.0f, 1.0f}, XORResult::One });
	data.AddSet({ {1.0f, 0.0f}, XORResult::One });
	data.AddSet({ {1.0f, 1.0f}, XORResult::Zero });

	NeuralNetworkTrainer trainer;
	std::chrono::seconds timeout(10);
	auto champ = Tests::TestingUtilities::TrainWithTimeout(trainer, data, timeout);
	std::cout << "Finished training in " << trainer.GetGenerationsPassed() << " generations\n";

	TrainingData<std::vector<float>, XORResult> expectedData;
	expectedData.AddSet({ { 1.0f, 0.0f }, XORResult::One });
	expectedData.AddSet({ { 1.0f, 1.0f }, XORResult::Zero });
	expectedData.AddSet({ { 1.0f, 1.0f }, XORResult::Zero });
	expectedData.AddSet({ { 1.0f, 1.0f }, XORResult::Zero });
	expectedData.AddSet({ { 0.0f, 1.0f }, XORResult::One });
	expectedData.AddSet({ { 0.0f, 0.0f }, XORResult::Zero });
	expectedData.AddSet({ { 0.0f, 0.0f }, XORResult::Zero });
	expectedData.AddSet({ { 0.0f, 1.0f }, XORResult::One });
	expectedData.AddSet({ { 0.0f, 0.0f }, XORResult::Zero });
	expectedData.AddSet({ { 1.0f, 1.0f }, XORResult::Zero });


	return Tests::TestingUtilities::TestNetwork(champ, expectedData);
}
