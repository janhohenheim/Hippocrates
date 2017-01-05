#pragma once
#include "phenotype/network_components/neuron_unit.hpp"
#include "phenotype/network_components/output_adaptor.hpp"
#include "phenotype/network_components/input_adaptor.hpp"

using namespace Hippocrates;
using namespace NetworkComponents;

auto NeuronUnit::HasSingleOutputAdaptor() const -> bool {
	return true;
}

auto NeuronUnit::HasSingleInputAdaptor() const -> bool {
	return true;
}

auto NeuronUnit::RecalculateOutputs() -> void {
	this->unit.SetInput(this->inputAdaptors[0].lastActivationValue);
	this->outputAdaptors[0].lastActionPotential = this->unit.RequestDataAndGetActionPotential();
}	