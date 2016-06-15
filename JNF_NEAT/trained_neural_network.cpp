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

string TrainedNeuralNetwork::GetGenomeAsString() const {
	string genomeString;
	for (auto& gene : GetGenome()) {
		genomeString +=
			"Gene with marking #" + to_string(gene.historicalMarking) + ":\n"
			+ "\t	from: " + to_string(gene.from) + "\n"
			+ "\t	to: " + to_string(gene.to) + "\n"
			+ "\t	weight: " + to_string(gene.weight) + "\n"
			+ "\t	is enabled: " + to_string(gene.isEnabled) + "\n";
			+ "\t	is recursive: " + to_string(gene.isRecursive) + "\n\n";
	}
	return genomeString;
}