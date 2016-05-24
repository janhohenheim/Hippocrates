#include "neural_network_trainer.h"
#include "xor_solver.h"
#include <iostream>
#include <time.h>

int main() {
    srand((unsigned)time(0U));
	std::cout << "Hello World" << std::endl;
	TrainingParameters params;
	params.numberOfInputs = 2;
	params.numberOfOutputs = 1;
	params.updatesPerGeneration = 4;

	int populationCount = 10;
    std::string file = "ChampGenome.genome";

	std::vector<IBody*> bodies;
	for (int i = 0; i < populationCount; ++i) {
        bodies.push_back(new XORSolver());
	}
	NeuralNetworkTrainer trainer(bodies, params);
	trainer.TrainUntilFitnessEquals(100);
	auto champ = trainer.GetTrainedNeuralNetwork();
    for (auto& body : bodies) {
        delete body;
    }

    champ.SaveToFile(file);
    auto outputs = champ.GetOutputs({0.0, 1.0});
    /*
    champ = TrainedNeuralNetwork::LoadFromFile(file);
    outputs = champ.GetOutputs({ 0.0, 1.0 });
    */
	std::vector<std::vector<float>> trainingData = { { 0.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 0.0f },{ 1.0f, 1.0f } };
	for (auto & t : trainingData) {
		std::cout << (int)(champ.GetOutputs(t).front() >= 0.5f) << "\t" << ((t.front() >= 0.5f) ^ (t.back() >= 0.5f)) << std::endl;
	}
	return 0;
}