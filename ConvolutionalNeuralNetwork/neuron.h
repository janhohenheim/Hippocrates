#pragma once
#include "matrix.h"
#include <vector>

namespace Convolutional {

class Neuron {
public:
	auto ExtractFeature(const Matrix& matrix) const -> Matrix;
	auto GetBias() const { return bias; }
	auto GetWeights() const { return weights; }

private:
	std::size_t bias = 0;
	std::vector<std::size_t> weights;
};

}