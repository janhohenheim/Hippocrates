#pragma once
#include <vector>
#include "type.hpp"

namespace Hippocrates {

class IBody {
public:
	IBody() = default;
	IBody(const IBody&) = default;
	IBody(IBody&&) = default;
	virtual ~IBody() = default;

	virtual auto operator=(const IBody&)&->IBody& = default;
	virtual auto operator=(IBody&&)&->IBody& = default;

	virtual auto Reset() -> void = 0;
	virtual auto Update(const Type::neuron_values_t& networkOutputs) -> void = 0;
	virtual auto HasFinishedTask() const -> bool = 0;
	virtual auto GetFitness() const -> Type::fitness_t = 0;

	virtual auto ProvideNetworkWithInputs() const -> Type::neuron_values_t= 0;

	virtual auto GetInputCount() const -> std::size_t = 0;
	virtual auto GetOutputCount() const -> std::size_t = 0;

	virtual auto GetMaximumFitness() const ->Type::fitness_t = 0;
};

}
