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
	trainer.TrainUntilGenerationEquals(100);
	auto champ = trainer.GetTrainedNeuralNetwork();
    for (auto& body : bodies) {
        delete body;
    }

    champ.SaveToFile(file);
    auto outputs = champ.GetOutputs({0.0, 1.0});
    for (auto& output : outputs) {
        std::cout << output << std::endl;
    }
    champ.LoadFromFile(file);
    outputs = champ.GetOutputs({ 0.0, 1.0 });
    for (auto& output : outputs) {
        std::cout << output << std::endl;
    }

	return 0;
}