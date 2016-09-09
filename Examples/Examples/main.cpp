#include "../../JNF_NEAT/neural_network_trainer.h"
#include "xor_solver.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <chrono>

using namespace std;
using namespace JNF_NEAT;

bool testingShit = false;


template<typename TimeT = std::chrono::milliseconds>
struct measure {
	template<typename F, typename ...Args>
	static typename TimeT::rep execution(F&& func, Args&&... args)
	{
		auto start = std::chrono::steady_clock::now();
		std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
		auto duration = std::chrono::duration_cast< TimeT>
			(std::chrono::steady_clock::now() - start);
		return duration.count();
	}
};

void TestingShitIgnoreThis(TrainingParameters& params, NeuralNetworkTrainer& trainer) {
	if (!testingShit) {
		return;
	}
	constexpr size_t numberOfShit = 20;

	long long totalTime = 0;
	for (size_t i = 0; i < numberOfShit; ++i) {
		cout << "Loop #" << (i + 1) << "/" << numberOfShit << "\n";
		vector<shared_ptr<IBody>> b;
		for (size_t i = 0; i < 50; ++i) {
			b.push_back(make_shared<XORSolver>());
		}
		NeuralNetworkTrainer t(b, params);

		// Enable this if you want to fill your SSD with a gigabyte of JSON
		t.loggingEnabled = false;

		auto timePassed = measure<>::execution([&t](double d) {t.TrainUntilFitnessEquals(d); }, 16.0);
		totalTime += timePassed;
		cout << "Finished in " << timePassed << "\n";
	}
	cout << "Total time: " << totalTime << "\n";
	cout << "Average time: " << (totalTime / numberOfShit) << "\n";
}

int main() {
	// Initilize Random Generator
	srand((unsigned)time(0U));

	// Prepare Parameters
	TrainingParameters params(2, 1);

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
	cout << (champ.GetOutputsUsingInputs({ 0.0, 0.0 }).front() >= 0.0) << endl;
	cout << (champ.GetOutputsUsingInputs({ 0.0, 1.0 }).front() >= 0.0) << endl;
	cout << (champ.GetOutputsUsingInputs({ 1.0, 0.0 }).front() >= 0.0) << endl;
	cout << (champ.GetOutputsUsingInputs({ 1.0, 1.0 }).front() >= 0.0) << endl;
	/*
	champ = TrainedNeuralNetwork::LoadFromFile(file);
	outputs = champ.GetOutputs({ 0.0, 1.0 });
	*/
	return 0;
}
