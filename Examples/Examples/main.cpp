#include "../../JNF_NEAT/neural_network_trainer.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <chrono>
#include "../../JNF_NEAT/training_data.h"

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


auto GetXOROutputs(TrainedNeuralNetwork& net) {
	auto XOR = [&net](const std::initializer_list<float> & in)	{
		auto result = net.GetOutputsUsingInputs(in);
		return (result.back() > result.front());
	};
	cout << XOR({ 0.0f, 0.0f }) << '\n';
	cout << XOR({ 0.0f, 1.0f }) << '\n';
	cout << XOR({ 1.0f, 0.0f }) << '\n';
	cout << XOR({ 1.0f, 1.0f }) << '\n';
}

int main() {
	// Initilize Random Generator
	srand(static_cast<unsigned>(time(nullptr)));

	enum class XORResults {
		Zero,
		One,
		ClassificationCount
	};
	TrainingData<std::vector<float>, XORResults> data;
	data.AddSet({ { 0.0f, 0.0f }, XORResults::Zero });
	data.AddSet({ { 0.0f, 1.0f }, XORResults::One });
	data.AddSet({ { 1.0f, 0.0f }, XORResults::One });
	data.AddSet({ { 1.0f, 1.0f }, XORResults::Zero });

	// Training
	NeuralNetworkTrainer trainer;
	trainer.loggingEnabled = false;
	auto champ = trainer.TrainSupervised(data, 50);
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
