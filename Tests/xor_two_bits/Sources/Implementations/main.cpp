#include <iostream>
#include "testing_utilities.hpp"

using namespace Hippocrates;

enum class XORResult {
	Zero,
	One,
	ClassificationCount
};

int main() {
	Training::Data<XORResult> data;
	data.AddSet( {0, 0}, XORResult::Zero );
	data.AddSet( {0, 1}, XORResult::One );
	data.AddSet( {1, 0}, XORResult::One );
	data.AddSet( {1, 1}, XORResult::Zero );

	Training::NeuralNetworkTrainer trainer;
	std::chrono::seconds timeout(10);
	auto champ = Tests::TestingUtilities::TrainWithTimeout(trainer, data, timeout);
	std::cout << "Finished training in " << trainer.GetGenerationsPassed() << " generations\n";
	return Tests::TestingUtilities::TestNetwork(champ, data);
}
