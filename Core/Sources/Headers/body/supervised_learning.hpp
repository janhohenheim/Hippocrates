#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>

#include "body.hpp"
#include "training/data.hpp"

namespace Hippocrates::Body {

template <typename Classification, std::size_t ClassificationCount>
class SupervisedLearning : public IBody {
public:
	using Data = Training::Data<Classification, ClassificationCount>;

	explicit SupervisedLearning(const Data& data) :
			trainingData{ data },
			inputCount{ data[0].input.size() }
	{};

	auto Reset() -> void override { currSetIndex = 0; error = 0; correctClassifications = 0; };
	auto Update(const Type::neuron_values_t& networkOutputs) -> void override;
	auto GetFitness() const -> Type::fitness_t override { return maxError - error; }

	auto HasFinishedTask() const -> bool override { return currSetIndex == trainingData.GetSize(); };
	auto ProvideNetworkWithInputs() const-> Type::neuron_values_t override {
		if (HasFinishedTask())
			throw std::runtime_error("Tried to get inputs out of Data that was already completly processed");
		return trainingData[currSetIndex].input;
	};

	auto GetInputCount() const -> std::size_t override { return inputCount; };
	auto GetOutputCount() const -> std::size_t override { return outputCount; };

	auto GetMaximumFitness() const -> Type::fitness_t override { return maxError - 0; };

private:
	const Type::neuron_value_t minActivation = ActivationFunction::GetFromParameters().GetMinOutput();
	const Type::neuron_value_t maxActivation = ActivationFunction::GetFromParameters().GetMaxOutput();

	const Data& trainingData;
	const std::size_t inputCount;
	const std::size_t outputCount = ClassificationCount;
	const Type::fitness_t maxError = trainingData.GetSize() * outputCount * std::abs(maxActivation - minActivation);

	std::size_t correctClassifications = 0;
	Type::fitness_t error = 0;
	std::size_t currSetIndex = 0;

};

template <typename Classification, std::size_t ClassificationCount>
auto SupervisedLearning<Classification, ClassificationCount>::Update(const Type::neuron_values_t& networkOutputs) -> void {
	const auto maxOutput = std::max_element(networkOutputs.begin(), networkOutputs.end());
	const auto outputIndex = static_cast<size_t>(std::distance(networkOutputs.begin(), maxOutput));
	const auto classificationAsNr = static_cast<size_t>(trainingData[currSetIndex].classification);

	if (outputIndex == classificationAsNr)
		++correctClassifications;

	if (correctClassifications == trainingData.GetSize()) {
		error = 0;
		++currSetIndex;
		return;
	}

	for (std::size_t i = 0; i < networkOutputs.size(); ++i) {
		const auto target = classificationAsNr == i ? maxActivation : minActivation;
		error += std::abs(networkOutputs[i] - target);
	}

	++currSetIndex;
}

}
