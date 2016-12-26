#pragma once

#include "type.hpp"
#include "interface.hpp"
#include "connection.hpp"

namespace Hippocrates::Phenotype::NetworkComponents {

template<typename TUnit>
class ITransformationUnit : public Utility::Interface {
	// TODO jnf: Is this the correct syntax?
	friend void InputAdaptor<TUnit>::Activate(Type::neuron_value_t activationValue) const;

public:
	using Interface::Interface;

	explicit ITransformationUnit(TUnit unit) : unit(std::move(unit)) {};

	std::vector<OutputAdaptor> outputAdaptors;
	std::vector<InputAdaptor<TUnit>> inputAdaptors;
	std::vector<NetworkComponents::Connection<TUnit>> incomingConnections;
	std::size_t layer = 0U;
	TUnit unit;

	virtual auto HasSingleOutputAdaptor() const -> bool = 0;
	virtual auto HasSingleInputAdaptor() const -> bool = 0;
	virtual auto RecalculateOutputs() const -> void = 0;

private:
	virtual auto InputAdaptorActivated(Type::neuron_value_t activationValue) -> void = 0;
};

}
