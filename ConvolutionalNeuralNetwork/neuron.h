#pragma once
#include "matrix.h"
#include <vector>

namespace Convolutional {

class Neuron {
public:
	virtual auto ExtractFeature(const Matrix& matrix) const -> Matrix;
	virtual auto GetBias() const -> std::size_t;
	virtual auto GetWeights() const -> std::vector<std::size_t>;
};

}