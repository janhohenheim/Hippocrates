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

void TestingShitIgnoreThis(NeuralNetworkTrainer& trainer) {
	if (!testingShit) {
		return;
	}
	constexpr size_t numberOfShit = 20;

	long long totalTime = 0;
	for (size_t i = 0; i < numberOfShit; ++i) {
		cout << "Loop #" << (i + 1) << "/" << numberOfShit << "\n";
		vector<shared_ptr<IBody>> bodies;
		for (size_t i = 0; i < 50; ++i) {
			bodies.push_back(make_shared<XORSolver>());
		}
		NeuralNetworkTrainer trainer(bodies);

		// Enable this if you want to fill your SSD with a gigabyte of JSON
		trainer.loggingEnabled = false;

		auto timePassed = measure<>::execution([&trainer](double d) {
			trainer.TrainUntilFitnessEquals(d); 
		}, 16.0);
		totalTime += timePassed;
		cout << "Finished in " << timePassed << "\n";
	}
	cout << "Total time: " << totalTime << "\n";
	cout << "Average time: " << (totalTime / numberOfShit) << "\n";
}

auto GetXOROutputs(TrainedNeuralNetwork & net)
{
	cout << (net.GetOutputsUsingInputs({0.0, 0.0}).front() >= 0.0) << "\n";
	cout << (net.GetOutputsUsingInputs({0.0, 1.0}).front() >= 0.0) << "\n";
	cout << (net.GetOutputsUsingInputs({1.0, 0.0}).front() >= 0.0) << "\n";
	cout << (net.GetOutputsUsingInputs({1.0, 1.0}).front() >= 0.0) << "\n";
}

int main() {
	// Initilize Random Generator
	srand((unsigned)time(0U));

	size_t populationCount = 50;

	// Create Bodies
	vector<shared_ptr<IBody>> bodies;
	for (size_t i = 0; i < populationCount; ++i) {
		bodies.push_back(make_shared<XORSolver>());
	}

	// Training
	NeuralNetworkTrainer trainer(move(bodies));
	trainer.loggingEnabled = true;
	trainer.TrainUntilFitnessEquals(16.0);

	// Get the best Neural Network trained
	auto champ = trainer.GetTrainedNeuralNetwork();
	TestingShitIgnoreThis(trainer);

	cout << "XOR outputs after training\n";
	GetXOROutputs(champ);
	string filename = "champ.nn";
	// Saving
	ofstream outFile(filename);
	champ.SaveToFile(outFile);
	outFile.close();

	//cout << "XOR outputs after saving\n";
	//GetXOROutputs(champ);

	// Loading
	ifstream inFile(filename);
	champ = TrainedNeuralNetwork::LoadFromFile(inFile);
	inFile.close();

	//cout << "XOR outputs after loading\n";
	//GetXOROutputs(champ);

	return 0;
}
