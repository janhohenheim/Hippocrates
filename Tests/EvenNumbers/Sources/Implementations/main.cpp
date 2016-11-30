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
	data.AddSet( { 5.0f },  Evenness::Uneven );
	// runs until here
	/*
	data.AddSet( { 6.0f },  Evenness::Even );
	data.AddSet( { 7.0f },  Evenness::Uneven );
	data.AddSet( { 8.0f },  Evenness::Even );
	data.AddSet( { 9.0f },  Evenness::Uneven );
	data.AddSet( { 10.0f }, Evenness::Even );
	data.AddSet( { 11.0f }, Evenness::Uneven );
	data.AddSet( { 12.0f }, Evenness::Even );
	data.AddSet( { 13.0f }, Evenness::Uneven );
	data.AddSet( { 14.0f }, Evenness::Even );
	data.AddSet( { 15.0f }, Evenness::Uneven );
	data.AddSet( { 16.0f }, Evenness::Even );
	data.AddSet( { 17.0f }, Evenness::Uneven );
	data.AddSet( { 18.0f }, Evenness::Even );
	data.AddSet( { 19.0f }, Evenness::Uneven );
	data.AddSet( { 20.0f }, Evenness::Even );
	*/
	Training::NeuralNetworkTrainer trainer;
	std::chrono::seconds timeout(45);
	auto champ = Tests::TestingUtilities::TrainWithTimeout(trainer, data, timeout);
	std::cout << "Finished training in " << trainer.GetGenerationsPassed() << " generations\n";

	Training::Data<Evenness> expectedData;
	expectedData.AddSet( { 21.0f }, Evenness::Uneven );
	expectedData.AddSet( { 22.0f }, Evenness::Even );
	expectedData.AddSet( { 23.0f }, Evenness::Uneven );
	expectedData.AddSet( { 24.0f }, Evenness::Even );
	expectedData.AddSet( { 25.0f }, Evenness::Uneven );
	expectedData.AddSet( { 26.0f }, Evenness::Even );
	expectedData.AddSet( { 27.0f }, Evenness::Uneven );
	expectedData.AddSet( { 28.0f }, Evenness::Even );
	expectedData.AddSet( { 29.0f }, Evenness::Uneven );
	expectedData.AddSet( { 30.0f }, Evenness::Even );
	expectedData.AddSet( { 31.0f }, Evenness::Uneven );
	expectedData.AddSet( { 32.0f }, Evenness::Even );
	expectedData.AddSet( { 33.0f }, Evenness::Uneven );
	expectedData.AddSet( { 34.0f }, Evenness::Even );
	expectedData.AddSet( { 35.0f }, Evenness::Uneven );
	expectedData.AddSet( { 36.0f }, Evenness::Even );
	expectedData.AddSet( { 37.0f }, Evenness::Uneven );
	expectedData.AddSet( { 38.0f }, Evenness::Even );
	expectedData.AddSet( { 39.0f }, Evenness::Uneven );
	expectedData.AddSet( { 40.0f }, Evenness::Even );

	return Tests::TestingUtilities::TestNetwork(champ, /*expectedData*/ data);
}
