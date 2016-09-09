#include <memory>
#include "trained_neural_network.h"

using namespace JNF_NEAT;
using namespace std;

auto TrainedNeuralNetwork::LoadFromFile(const ifstream& fileName) -> TrainedNeuralNetwork {
	// TODO jnf Implementation
	unique_ptr<TrainingParameters> params(new TrainingParameters(2, 1));
	TrainedNeuralNetwork net(*params.get());
	return net;
}

auto TrainedNeuralNetwork::SaveToFile(std::ofstream& file) const -> void {
	file << GetGenome().GetJSON();
}
