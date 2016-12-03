#pragma once
#include <algorithm>
#include <cmath>

#include "body.hpp"
#include "training/data.hpp"

namespace Hippocrates::Body {

template <typename Classification, std::size_t ClassificationCount>
class SupervisedLearning : public IBody {
public:
	using Data = Training::Data<Classification, ClassificationCount>;

	explicit SupervisedLearning(const Data& data) :
			trainingData { data },
			inputCount{data[0].input.size()}
	{};

	auto Reset() -> void override { currSetIndex = 0; error = 0; };
	auto Update(const Type::neuron_values_t& networkOutputs) -> void override;
	auto GetFitness() const -> Type::fitness_t override { return std::pow(maxError - error, 2); }

	auto HasFinishedTask() const -> bool override { return currSetIndex == trainingData.GetSize(); };
	auto ProvideNetworkWithInputs() const-> Type::neuron_values_t override {
		if (HasFinishedTask())
			throw std::runtime_error("Tried to get inputs out of Data that was already completly processed");
		return trainingData[currSetIndex].input;
	};

	auto GetInputCount() const -> std::size_t override { return inputCount; };
	auto GetOutputCount() const -> std::size_t override { return outputCount; };

	auto GetMaximumFitness() const -> Type::fitness_t override { return std::pow(maxError - 0, 2); };

private:
	const Data& trainingData;
	const std::size_t inputCount;

	std::size_t currSetIndex = 0;
	const std::size_t outputCount = ClassificationCount;
	const Type::fitness_t maxError = trainingData.GetSize() * outputCount * std::abs(-1.0 - 1.0);
	Type::fitness_t error = 0;
};

template <typename Classification, std::size_t ClassificationCount>
auto SupervisedLearning<Classification, ClassificationCount>::Update(const Type::neuron_values_t& networkOutputs) -> void {
	for (std::size_t i = 0; i < networkOutputs.size(); ++i) {
		if (static_cast<size_t>(trainingData[currSetIndex].classification) == i) {
			error += std::abs(networkOutputs[i] - 1.0);
		} else {
			error += std::abs(-1.0 - networkOutputs[i]);
		}
	}
	++currSetIndex;
}

}
