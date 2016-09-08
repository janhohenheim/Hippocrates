#pragma once
#include "matrix.h"
#include "isubsampler.h"
#include <vector>

namespace Convolutional {
namespace SubSampler {

class Neuron : public ISubSampler {
public:
	auto ProcessMatrix(Matrix::Position position, const Matrix& matrix) const -> Matrix override;
	auto GetBias() const { return bias; }
	auto GetWeights() const { return weights; }

private:
	static auto sigmoid(Matrix::elementType n) -> double;
	double bias = 0;
	std::vector<double> weights;
	Matrix::Size receptiveField;
};

}
}
