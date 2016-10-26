#include "testing_utilities.hpp"

using namespace std;
using namespace Hippocrates;

enum class Evenness {
	Even,
	Uneven,
	ClassificationCount
};

int main() {
	srand(static_cast<unsigned>(time(nullptr)));

	constexpr auto maxValue = 40.0f;

	TrainingData<std::vector<float>, Evenness> data;
	data.AddSet({ { 1.0f / maxValue },  Evenness::Uneven });
	data.AddSet({ { 2.0f / maxValue },  Evenness::Even });
	data.AddSet({ { 3.0f / maxValue },  Evenness::Uneven });
	data.AddSet({ { 4.0f / maxValue },  Evenness::Even });
	data.AddSet({ { 5.0f / maxValue },  Evenness::Uneven });
	data.AddSet({ { 6.0f / maxValue },  Evenness::Even });
	data.AddSet({ { 7.0f / maxValue },  Evenness::Uneven });
	data.AddSet({ { 8.0f / maxValue },  Evenness::Even });
	data.AddSet({ { 9.0f / maxValue },  Evenness::Uneven });
	data.AddSet({ { 10.0f / maxValue }, Evenness::Even });
	data.AddSet({ { 11.0f / maxValue }, Evenness::Uneven });
	data.AddSet({ { 12.0f / maxValue }, Evenness::Even });
	data.AddSet({ { 13.0f / maxValue }, Evenness::Uneven });
	data.AddSet({ { 14.0f / maxValue }, Evenness::Even });
	data.AddSet({ { 15.0f / maxValue }, Evenness::Uneven });
	data.AddSet({ { 16.0f / maxValue }, Evenness::Even });
	data.AddSet({ { 17.0f / maxValue }, Evenness::Uneven });
	data.AddSet({ { 18.0f / maxValue }, Evenness::Even });
	data.AddSet({ { 19.0f / maxValue }, Evenness::Uneven });
	data.AddSet({ { 20.0f / maxValue }, Evenness::Even });

	TrainingParameters parameters;
	parameters.structure.allowRecurrentConnections = true;

	NeuralNetworkTrainer trainer(parameters);
	
	auto champ = trainer.TrainSupervised(data, 50);

	TrainingData<std::vector<float>, Evenness> expectedData;
	expectedData.AddSet({ { 21.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 22.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 23.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 24.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 25.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 26.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 27.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 28.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 29.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 30.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 31.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 32.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 33.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 34.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 35.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 36.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 37.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 38.0f / maxValue }, Evenness::Even });
	expectedData.AddSet({ { 39.0f / maxValue }, Evenness::Uneven });
	expectedData.AddSet({ { 40.0f / maxValue }, Evenness::Even });

	return Tests::TestingUtilities::TestNetwork(champ, expectedData);
}
