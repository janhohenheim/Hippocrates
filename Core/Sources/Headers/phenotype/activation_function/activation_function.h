#pragma once
#include "utility\interface.h"
#include "type.hpp"

namespace Hippocrates::Phenotype::ActivationFunction {

class IActivationFunction : public Utility::Interface {
public:
	using Interface::Interface;

	virtual auto operator() (Type::neuron_value_t totalNeuronValue) const -> Type::neuron_value_t = 0;

	virtual auto GetMinOutput() const -> Type::neuron_value_t = 0;
	virtual auto GetMaxOutput() const -> Type::neuron_value_t = 0;
};

}
