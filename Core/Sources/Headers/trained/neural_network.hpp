#pragma once
#include "../phenotype/neural_network.hpp"

namespace Hippocrates {
namespace Trained {

class NeuralNetwork : public Phenotype::NeuralNetwork {
public:
	using Phenotype::NeuralNetwork::NeuralNetwork;
};

}
}
