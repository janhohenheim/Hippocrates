#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>
#include "testing_utilities.h"
#include "../Headers/sine_body.h"
#include <cmath>
using namespace std;
using namespace Hippocrates;
using namespace Tests;
using namespace Sine;

int TestNetwork(TrainedNeuralNetwork champ) {
	auto errorCount = 0;

	for (size_t i = 0; i < 100; ++i) {
		auto LO = static_cast<float>(-M_PI);
		auto HI = static_cast<float>(M_PI);
		auto dataSet = static_cast<float>(rand());

		auto networkResult = champ.GetOutputsUsingInputs({LO + dataSet / (static_cast<float>(RAND_MAX) / (HI - LO))})[0];
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

	TrainingParameters parameters;
	parameters.structure.areRecursiveConnectionsAllowed = false;

	NeuralNetworkTrainer trainer(parameters);
	trainer.loggingEnabled = false;

	#ifdef CI
		trainer.loggingEnabled = false;
	#endif

	std::vector<SineBody> bodies(100);
	SpeciesManager::Bodies trainingBodies(bodies.begin(), bodies.end());

	auto champ = trainer.TrainUnsupervised(trainingBodies);

	return TestNetwork(champ);
}
