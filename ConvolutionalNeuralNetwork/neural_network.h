#pragma once
#include <memory>
#include <functional>
#include "multi_dimensional_matrix.h"
#include "ipooler.h"
#include "neuron.h"
#include "multi_dimensional_matrix_parser.h"

namespace Convolutional {

class NeuralNetwork {
private:
    using Parser = MultiDimensionalMatrixParser;

public:
    NeuralNetwork(MultiDimensionalMatrix matrix);
    template <typename T>
    NeuralNetwork(const T& parsableData) : 
        NeuralNetwork(std::move(Parser::Parse(std::forward(parsableData)))) {}

	auto Pool(const IPooler& pooler) -> void;
	auto Subsample(const Neuron& neuron) -> void;
	auto ApplyToAllMatrices(std::function<Matrix(const Matrix&)> function) -> void;

private:
	MultiDimensionalMatrix matrix;
};

}