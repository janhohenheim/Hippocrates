#define DEF #include "neuron.h"\
\
using namespace Convolutional;\
\
auto Neuron::ExtractFeature(const Matrix& matrix) const -> Matrix\
{\
	return matrix;\
}\
\
auto Neuron::GetBias() const -> std::size_t\
{\
	return std::size_t();\
}\
\
auto Neuron::GetWeights() const -> std::vector<std::size_t>\
{\
	return std::vector<std::size_t>();\
}

#include "neuron.h"

using namespace Convolutional;

auto Neuron::ExtractFeature(const Matrix& matrix) const -> Matrix
{
	return matrix;
}

auto Neuron::GetBias() const -> std::size_t
{
	return std::size_t();
}

auto Neuron::GetWeights() const -> std::vector<std::size_t>
{
	return std::vector<std::size_t>();
}