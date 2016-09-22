#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <cmath>
#include "testing_utilities.h"
#include "../Headers/sine_body.h"
using namespace std;
using namespace Hippocrates;
using namespace Tests;
using namespace Sine;

int TestNetwork(TrainedNeuralNetwork& champ) {
	auto errorCount = 0;

	for (size_t i = 0; i < 100; ++i) {
		static auto RandomFloat = [](float a, float b) {
			auto random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			auto diff = b - a;
			auto r = random * diff;
			return a + r;
		};

		auto dataSet = RandomFloat(-M_PI, M_PI);

		auto networkResult = champ.GetOutputsUsingInputs({dataSet / static_cast<float>(M_PI)})[0];
		auto distanceToCorrectResult = abs(sin(dataSet) - networkResult);

		if (100 - (distanceToCorrectResult * 50) < 90) {
			std::cout << "Incorrect result: " << sin(dataSet) << " -> " << networkResult << std::endl;
			errorCount++;
		}
	}

	return errorCount;
}

int main() {
	srand(static_cast<unsigned>(time(nullptr)));

	NeuralNetworkTrainer trainer;

	std::vector<SineBody> bodies(100);
	SpeciesManager::Bodies trainingBodies(bodies.begin(), bodies.end());

	auto champ = trainer.TrainUnsupervised(trainingBodies);

	return TestNetwork(champ);
}
