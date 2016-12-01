#include <iostream>
#include "testing_utilities.hpp"

using namespace Hippocrates;

enum class Evenness {
	Even,
	Uneven,
	ClassificationCount
};

int main() {
	Training::Data<Evenness> data;
	data.AddSet( { 1.0f },  Evenness::Uneven );
	data.AddSet( { 2.0f },  Evenness::Even );
	data.AddSet( { 3.0f },  Evenness::Uneven );
	data.AddSet( { 4.0f },  Evenness::Even );

	Training::NeuralNetworkTrainer trainer;
	std::chrono::seconds timeout(45);
	auto champ = Tests::TestingUtilities::TrainWithTimeout(trainer, data, timeout);
	std::cout << "Finished training in " << trainer.GetGenerationsPassed() << " generations\n";

	return Tests::TestingUtilities::TestNetwork(champ, data);
}
