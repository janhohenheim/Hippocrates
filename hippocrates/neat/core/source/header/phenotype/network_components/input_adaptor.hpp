#pragma once
#include "phenotype/neuron.hpp"

namespace Hippocrates::Phenotype::NetworkComponents {

template<typename TUnit>
class InputAdaptor {
private:
	ITransformationUnit<TUnit>& owner;

public:
	explicit InputAdaptor(ITransformationUnit<TUnit>& adaptorOwner) : owner(adaptorOwner) { }

	// TODO jnf: will this work? VS2017 RC has no compilation error but resharper complains.
	auto Activate(Type::neuron_value_t activationValue) const -> void { owner->InputAdaptorActivated(activationValue); }
};

}
