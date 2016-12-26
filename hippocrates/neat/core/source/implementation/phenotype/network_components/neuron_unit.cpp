#pragma once
#include "phenotype/network_components/neuron_unit.hpp"
#include "phenotype/network_components/output_adaptor.hpp"
#include "phenotype/network_components/input_adaptor.hpp"

using namespace Hippocrates;
using namespace NetworkComponents;

auto NeuronUnit::HasSingleOutputAdaptor() -> bool {
	return true;
}

auto NeuronUnit::GetSingleOutputAdaptor() -> OutputAdaptor {

}

auto NeuronUnit::HasSingleInputAdaptor() -> bool {
	return true;
}

auto NeuronUnit::GetSingleInputAdaptor() -> InputAdaptor<Neuron> {

}

auto NeuronUnit::RecalculateOutputs() -> void {

}

auto NeuronUnit::InputAdaptorActivated(Type::neuron_value_t activationValue) -> void {
		
}
	

