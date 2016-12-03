#pragma once
#include <cmath>

#include "activation_function.hpp"

namespace Hippocrates::Phenotype::ActivationFunction {

class Tanh : public IActivationFunction {
public:
	using IActivationFunction::IActivationFunction;

	auto operator() (Type::neuron_value_t totalNeuronValue) const -> Type::neuron_value_t override {
		return std::tanh(totalNeuronValue);
	}

	auto GetMinOutput() const -> Type::neuron_value_t override {
		return -1;
	}
	auto GetMaxOutput() const -> Type::neuron_value_t override {
		return 1;
	}
};

}
