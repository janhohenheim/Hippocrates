#pragma once
#include <vector>

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
	virtual auto Update(const std::vector<float>& networkOutputs) -> void = 0;
	virtual auto HasFinishedTask() const -> bool = 0;
	virtual auto GetFitness() const -> double = 0;

	virtual auto ProvideNetworkWithInputs() const -> std::vector<float> = 0;

	virtual auto GetInputCount() const -> std::size_t = 0;
	virtual auto GetOutputCount() const -> std::size_t = 0;

	virtual auto GetMaximumFitness() const -> double = 0;
};

}
