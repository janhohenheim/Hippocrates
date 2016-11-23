#pragma once
#include "../neural_network.hpp"
#include "../training_data.hpp"

namespace Convolutional::Learning {

	template<typename Classification>
	class ILearningMethod {
	public:
		ILearningMethod(
			NeuralNetwork<Classification>& neuralNetwork,
			const TrainingData<Classification>& data) 
			:
			neuralNetwork(neuralNetwork),
			data(data)	{}
		virtual ~ILearningMethod() = default;
		
		virtual auto BeginEpoch() -> void = 0;
		virtual auto EvaluateSet(typename TrainingData<Classification>::const_iterator set) -> void = 0;
		virtual auto EndEpoch() -> void = 0;

	protected:
		NeuralNetwork<Classification>& neuralNetwork;
		const TrainingData<Classification>& data;
	};

	template<typename Classification>
	class memes : public ILearningMethod<Classification> {
	public:
		using ILearningMethod::ILearningMethod;
		auto BeginEpoch() -> void override {}
		auto EvaluateSet(typename TrainingData<Classification>::const_iterator set) -> void override {}
		auto EndEpoch() -> void override {}
	};

}