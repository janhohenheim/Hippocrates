#pragma once
#include <cmath>

#include "activation_function.hpp"

namespace Hippocrates::ActivationFunction {

class FastSigmoid : public IActivationFunction {
public:
	using IActivationFunction::IActivationFunction;

	auto operator() (Type::neuron_value_t totalNeuronValue) const -> Type::neuron_value_t override {
		return totalNeuronValue / (Type::neuron_value_t(1) + abs(totalNeuronValue));
	}

	auto GetMinOutput() const -> Type::neuron_value_t override {
		return -1;
	}

	auto GetMaxOutput() const -> Type::neuron_value_t override {
		return 1;
	}
};

}
