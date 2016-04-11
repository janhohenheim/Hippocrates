#include "neural_network_trainer.h"
#include <iostream>
#include <time.h>

int main() {
    srand((unsigned)time(0U));
	std::cout << "Hello World" << std::endl;

	TrainingParameters params;
	params.numberOfInputs = 3;
	params.numberOfOutputs = 3;

	std::vector<ITrainable *> population;
	NeuralNetworkTrainer trainer(population, params);
	//trainer.TrainUntilFitnessEquals(100);

	return 0;
}