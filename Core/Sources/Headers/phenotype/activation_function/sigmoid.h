#pragma once
#include "activation_function.h"

namespace Hippocrates::Phenotype::ActivationFunction {

class Sigmoid : public IActivationFunction {
public:
	using IActivationFunction::IActivationFunction;

	virtual auto operator() (Type::neuron_value_t totalNeuronValue) const -> Type::neuron_value_t = 0;

	virtual auto GetMinOutput() const -> Type::neuron_value_t = 0;
	virtual auto GetMaxOutput() const -> Type::neuron_value_t = 0;
};

}
