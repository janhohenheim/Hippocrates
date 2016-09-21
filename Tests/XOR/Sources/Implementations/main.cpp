#include <fstream>
#include <chrono>

// TODO: Replace with library import
#include "network_tester.h"


using namespace std;
using namespace JNF_NEAT;

enum class XORResult {
	Zero,
	One,
	ClassificationCount
};



auto SaveNetwork(TrainedNeuralNetwork &champ, string filename) {
	ofstream outFile(filename);
	champ.SaveToFile(outFile);
	outFile.close();
}

auto LoadNetwork(string filename) {
	ifstream inFile(filename);
	auto champ = TrainedNeuralNetwork::LoadFromFile(inFile);
	inFile.close();

	return champ;
}

int main() {
	srand(static_cast<unsigned>(time(nullptr)));

	TrainingData<std::vector<float>, XORResult> data;
	data.AddSet({ {0.0f, 0.0f}, XORResult::Zero });
	data.AddSet({ {0.0f, 1.0f}, XORResult::One });
	data.AddSet({ {1.0f, 0.0f}, XORResult::One });
	data.AddSet({ {1.0f, 1.0f}, XORResult::Zero });

	NeuralNetworkTrainer trainer;
	trainer.loggingEnabled = false;

	#ifdef CI
		trainer.loggingEnabled = false;
	#endif

	auto champ = trainer.TrainSupervised(data, 50);

	SaveNetwork(champ, "champ.nn");
	LoadNetwork("champ.nn");

	return Tests::TestingUtilities::TestNetwork(champ, data);
}
