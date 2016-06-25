#include <memory>
#include "trained_neural_network.h"

using namespace JNF_NEAT;
using namespace std;

TrainedNeuralNetwork TrainedNeuralNetwork::LoadFromFile(const string& fileName) {
	// TODO jnf Implementation
	unique_ptr<TrainingParameters> params (new TrainingParameters);
	params->numberOfInputs = 2;
	params->numberOfOutputs = 1;
	params->updatesPerGeneration =30;
	TrainedNeuralNetwork net(*params.get());
	return net;
}

void TrainedNeuralNetwork::SaveToFile(const string& fileName) const {
	// TODO jnf Implementation
}