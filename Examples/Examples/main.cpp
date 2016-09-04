#include "../../JNF_NEAT/neural_network_trainer.h"
#include "xor_solver.h"
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;
using namespace JNF_NEAT;

// Enable this if you want to fill your SSD with a gigabyte of JSON
bool testingShit = false;

void TestingShitIgnoreThis(TrainingParameters& params, NeuralNetworkTrainer& trainer){
	if (!testingShit) {
		return;
	}
	for (size_t i = 0; i < 100; ++i) {
		cout << "Loop #" << i << endl;
		vector<shared_ptr<IBody>> b;
		for (size_t i = 0; i < 50; ++i) {
			b.push_back(make_shared<XORSolver>());
		}
		NeuralNetworkTrainer t(b, params);
		t.loggingEnabled = true;
		t.TrainUntilFitnessEquals(16.0);
	}
}

int main() {
	// Initilize Random Generator
	srand((unsigned)time(0U));

	// Prepare Parameters
	TrainingParameters params(2,1);

	size_t populationCount = 50;

	// Create Bodies
	vector<shared_ptr<IBody>> bodies;
	for (size_t i = 0; i < populationCount; ++i) {
		bodies.push_back(make_shared<XORSolver>());
	}

	// Training
	NeuralNetworkTrainer trainer(move(bodies), params);
	trainer.loggingEnabled = false;
	trainer.TrainUntilFitnessEquals(16.0);

	// Get the best Neural Network trained
	auto champ = trainer.GetTrainedNeuralNetwork();
	TestingShitIgnoreThis(params, trainer);

	// Saving and Loading
	string file = "champ.nn";
	champ.SaveToFile(file);
	cout << to_string(champ.GetOutputsUsingInputs({0.0, 0.0}).front() >= 0.0) << endl;
	cout << to_string(champ.GetOutputsUsingInputs({0.0, 1.0}).front() >= 0.0) << endl;
	cout << to_string(champ.GetOutputsUsingInputs({1.0, 0.0}).front() >= 0.0) << endl;
	cout << to_string(champ.GetOutputsUsingInputs({1.0, 1.0}).front() >= 0.0) << endl;
	/*
	champ = TrainedNeuralNetwork::LoadFromFile(file);
	outputs = champ.GetOutputs({ 0.0, 1.0 });
	*/
	return 0;
}
