#pragma once
#include "neuron.hpp"


namespace Hippocrates::Phenotype::NetworkComponents {

class OutputAdaptor {
public:
	Type::neuron_value_t lastActionPotential = 0.0f;

};

}
