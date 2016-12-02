#pragma once
#include "utility\interface.h"
#include "type.hpp"

namespace Hippocrates::Phenotype {

class IActivationFunctor : public Utility::Interface {
public:
	using Interface::Interface;

	virtual auto operator() (Type::neuron_value_t) const -> Type::neuron_value_t = 0;

	virtual auto GetMinOutput() const -> Type::neuron_value_t = 0;
	virtual auto GetMaxOutput() const -> Type::neuron_value_t = 0;
};

}