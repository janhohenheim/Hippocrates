#include "testing_utilities.hpp"

using namespace std;
using namespace Hippocrates;

enum class XORResult {
	Zero,
	One,
	ClassificationCount
};

int main() {
	srand(static_cast<unsigned>(time(nullptr)));

	TrainingData<std::vector<float>, XORResult> data;
	data.AddSet({ {0.0f, 0.0f}, XORResult::Zero });
	data.AddSet({ {0.0f, 1.0f}, XORResult::One });
	data.AddSet({ {1.0f, 0.0f}, XORResult::One });
	data.AddSet({ {1.0f, 1.0f}, XORResult::Zero });

	NeuralNetworkTrainer trainer;

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
	auto champ = trainer.TrainSupervised(data, 150);

	std::cout << trainer.GetGenerationsPassed() << '\n';

	return Tests::TestingUtilities::TestNetwork(champ, expectedData);
}
