#pragma once
#include "transformation_unit.hpp"
#include "phoenotype/neuron.hpp"

using namespace Hippocrates;
using namespace Phenotype;

namespace Hippocrates::Phenotype::NetworkComponents {

class NeuronUnit : public ITransformationUnit<Neuron> {

public:
	auto HasSingleOutputAdaptor() const -> bool = 0;
	auto GetSingleOutputAdaptor() const->OutputAdaptor = 0;
	auto HasSingleInputAdaptor() const -> bool = 0;
	auto GetSingleInputAdaptor() const->InputAdaptor<Neuron> = 0;
	auto RecalculateOutputs() const -> void = 0;

private:
	auto InputAdaptorActivated(Type::neuron_value_t activationValue) -> void = 0;
};

}
