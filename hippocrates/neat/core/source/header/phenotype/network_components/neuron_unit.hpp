#pragma once
#include "transformation_unit.hpp"
#include "phenotype/neuron.hpp"

using namespace Hippocrates;
using namespace Phenotype;

namespace Hippocrates::Phenotype::NetworkComponents {

class NeuronUnit : public ITransformationUnit<Neuron> {

public:
	auto HasSingleOutputAdaptor() const -> bool = 0;
	auto HasSingleInputAdaptor() const -> bool = 0;
	virtual auto RecalculateOutputs() -> void;

private:
	auto InputAdaptorActivated(Type::neuron_value_t activationValue) -> void = 0;
};

}
