#pragma once
#include "body.hpp"
#include "training_data.hpp"
#include <algorithm>

namespace Hippocrates {

template <typename InputType, typename Classification, std::size_t ClassificationCount>
class SupervisedTrainigBody : public IBody {
public:
	using Data = TrainingData<InputType, Classification, ClassificationCount>;

	explicit SupervisedTrainigBody(const Data& data) :
			trainingData{ data },
			inputCount{data.begin()->input.size()},
			outputCount{ClassificationCount},
			maxFitness{static_cast<double>(data.GetSize())}
	{};

	auto Reset() -> void override { currSet = trainingData.begin(); fitness = 0.0; };
	auto Update(const std::vector<float>& networkOutputs) -> void override;
	auto GetFitness() const -> double override { return fitness; }

	auto HasFinishedTask() const -> bool override { return currSet == trainingData.end(); };
	auto ProvideNetworkWithInputs() const->std::vector<float> override {
		if (HasFinishedTask())
			throw std::runtime_error("Tried to get inputs out of trainingdata that was already completly processed");
		return currSet->input;
	};

	auto GetInputCount() const -> std::size_t override { return inputCount; };
	auto GetOutputCount() const -> std::size_t override { return outputCount; };

	auto GetMaximumFitness() const -> double override { return maxFitness; };

private:
	const Data& trainingData;
	typename Data::const_iterator currSet = trainingData.begin();
	double fitness = 0.0;
	const size_t inputCount;
	const size_t outputCount;
	const double maxFitness;
};

template <typename InputType, typename Classification, std::size_t ClassificationCount>
auto SupervisedTrainigBody<InputType, Classification, ClassificationCount>::Update(const std::vector<float>& networkOutputs) -> void {
	auto maxOutput = std::distance(networkOutputs.begin(), std::max_element(networkOutputs.begin(), networkOutputs.end()));
	if (static_cast<size_t>(maxOutput) == static_cast<size_t>(currSet->classification)) {
		fitness += 1.0;
	}
	++currSet;
}

}
