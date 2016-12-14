#pragma once
#include <vector>
#include "type.hpp"
#include "utility/interface.hpp"

namespace Hippocrates::Body {

class IBody : public Utility::Interface {
public:
	using Utility::Interface::Interface;

	virtual auto Reset() -> void = 0;
	virtual auto Update(const Type::neuron_values_t& networkOutputs) -> void = 0;
	virtual auto HasFinishedTask() const -> bool = 0;
	virtual auto GetFitness() const -> Type::fitness_t = 0;

	virtual auto ProvideNetworkWithInputs() const -> Type::neuron_values_t = 0;

	virtual auto GetInputCount() const -> std::size_t = 0;
	virtual auto GetOutputCount() const -> std::size_t = 0;

	virtual auto GetMaximumFitness() const ->Type::fitness_t = 0;
};

}
