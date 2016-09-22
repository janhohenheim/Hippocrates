#include "testing_utilities.h"

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

	auto champ = trainer.TrainSupervised(data, 50);

	return Tests::TestingUtilities::TestNetwork(champ, data);
}
