#pragma once
#include <memory>
#include <functional>
#include "multi_dimensional_matrix.h"
#include "ipooler.h"
#include "neuron.h"

namespace Convolutional {

class NeuralNetwork {
public:
	NeuralNetwork(MultiDimensionalMatrix matrix);

	auto Pool(const IPooler& pooler) -> void;
	auto Subsample(const Neuron& neuron) -> void;
	auto ApplyToAllMatrices(std::function<Matrix(const Matrix&)> function) -> void;

private:
	MultiDimensionalMatrix matrix;
};

}