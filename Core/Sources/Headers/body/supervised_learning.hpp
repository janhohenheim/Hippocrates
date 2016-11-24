#pragma once
#include <algorithm>

#include "body.hpp"
#include "training/data.hpp"

namespace Hippocrates::Body {

template <typename Classification, std::size_t ClassificationCount>
class SupervisedLearning : public IBody {
public:
	using Data = Training::Data<Classification, ClassificationCount>;

	explicit SupervisedLearning(const Data& data) :
			trainingData { data },
			inputCount{data.begin()->input.size()},
			outputCount{ClassificationCount},
			maxFitness{static_cast<Type::fitness_t>(data.GetSize())}
	{};

	auto Reset() -> void override { currSet = trainingData.begin(); fitness = 0.0; };
	auto Update(const Type::neuron_values_t& networkOutputs) -> void override;
	auto GetFitness() const -> Type::fitness_t override { return fitness; }

	auto HasFinishedTask() const -> bool override { return currSet == trainingData.end(); };
	auto ProvideNetworkWithInputs() const-> Type::neuron_values_t override {
		if (HasFinishedTask())
			throw std::runtime_error("Tried to get inputs out of Data that was already completly processed");
		return currSet->input;
	};

	auto GetInputCount() const -> std::size_t override { return inputCount; };
	auto GetOutputCount() const -> std::size_t override { return outputCount; };

	auto GetMaximumFitness() const -> Type::fitness_t override { return maxFitness; };

private:
	const Data& trainingData;
	typename Data::const_iterator currSet = trainingData.begin();
	Type::fitness_t fitness = static_cast<Type::fitness_t>(0.0);
	const std::size_t inputCount;
	const std::size_t outputCount;
	const Type::fitness_t maxFitness;
};

template <typename Classification, std::size_t ClassificationCount>
auto SupervisedLearning<Classification, ClassificationCount>::Update(const Type::neuron_values_t& networkOutputs) -> void {
	auto maxOutput = std::distance(networkOutputs.begin(), std::max_element(networkOutputs.begin(), networkOutputs.end()));
	if (static_cast<size_t>(maxOutput) == static_cast<size_t>(currSet->classification)) {
		fitness += static_cast<Type::fitness_t>(1.0);
	}
	++currSet;
}

}