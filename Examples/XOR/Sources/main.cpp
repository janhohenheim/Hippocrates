#include "xor_solver.h"

// TODO: Replace with library imports
#include "../../../Core/Sources/training_parameters.h"
#include "../../../Core/Sources/neural_network_trainer.h"

#include <iostream>

using namespace std;
using namespace JNF_NEAT;

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

void Benchmark() {
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

int testNetowrk(TrainedNeuralNetwork & net) {
	int errorCount = 0;

	if (net.GetOutputsUsingInputs({0.0, 0.0}).front() >= 0.0) {
		cout << "Failed with inputs 0 / 0" << std::endl;
		errorCount++;
	};

	if (net.GetOutputsUsingInputs({0.0, 1.0}).front() < 0.0) {
		cout << "Failed with inputs 0 / 1" << std::endl;
		errorCount++;
	};

	if (net.GetOutputsUsingInputs({1.0, 0.0}).front() < 0.0) {
		cout << "Failed with inputs 1 / 0" << std::endl;
		errorCount++;
	};

	if (net.GetOutputsUsingInputs({1.0, 1.0}).front() >= 0.0) {
		cout << "Failed with inputs 1 / 1" << std::endl;
		errorCount++;
	};

	return errorCount;
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
	trainer.loggingEnabled = false;
	trainer.TrainUntilFitnessEquals(16.0);
	// Benchmark();

	// Get the best Neural Network trained
	auto champ = trainer.GetTrainedNeuralNetwork();

//	cout << "XOR outputs after training\n";
//	GetXOROutputs(champ);

	int errorCount = testNetowrk(champ);

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

	return errorCount;
}
