#pragma once

#include "type.hpp"
#include "interface.hpp"
#include "connection.hpp"

namespace Hippocrates::Phenotype::NetworkComponents {

class ITransformationUnit : public Utility::Interface {
	// TODO jnf: Is this the correct syntax?
	friend void InputAdaptor::Activate(Type::neuron_value_t activationValue) const;

public:
	using Interface::Interface;

	std::vector<OutputAdaptor> outputAdaptors;
	std::vector<InputAdaptor> inputAdaptors;
	std::vector<NetworkComponents::Connection> incomingConnections;
	std::size_t layer = 0U;

	virtual auto HasSingleOutputAdaptor() const -> bool = 0;
	virtual auto GetSingleOutputAdaptor() const -> OutputAdaptor = 0;
	virtual auto HasSingleInputAdaptor() const -> bool = 0;
	virtual auto GetSingleInputAdaptor() const -> OutputAdaptor = 0;
	virtual auto RecalculateOutputs() const -> void = 0;

private:
	virtual auto InputAdaptorActivated(Type::neuron_value_t activationValue) -> void = 0;
};

}
