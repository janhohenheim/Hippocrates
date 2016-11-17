#include "testing_utilities.hpp"

using namespace std;
using namespace Hippocrates;

enum class XORResult {
	Zero,
	One,
	ClassificationCount
};

int main() {
	Data<XORResult> data;
	data.AddSet({0, 0, 0}, XORResult::Zero);
	data.AddSet({0, 1, 0}, XORResult::One);
	data.AddSet({1, 0, 0}, XORResult::One);
	data.AddSet({1, 0, 1}, XORResult::Zero);
	data.AddSet({1, 1, 1}, XORResult::Zero);

	NeuralNetworkTrainer trainer;
	std::chrono::seconds timeout(10);
	auto champ = Tests::TestingUtilities::TrainWithTimeout(trainer, data, timeout);
	std::cout << "Finished training in " << trainer.GetGenerationsPassed() << " generations\n";

	Data<XORResult> expectedData;
	data.AddSet({0, 0, 0}, XORResult::Zero);
	data.AddSet({0, 0, 1}, XORResult::One);
	data.AddSet({0, 1, 1}, XORResult::Zero);
	data.AddSet({1, 0, 1}, XORResult::Zero);
	data.AddSet({1, 0, 0}, XORResult::One);
	data.AddSet({1, 1, 1}, XORResult::Zero);
	data.AddSet({1, 1, 0}, XORResult::Zero);
	data.AddSet({0, 1, 0}, XORResult::One);


	return Tests::TestingUtilities::TestNetwork(champ, expectedData);
}
