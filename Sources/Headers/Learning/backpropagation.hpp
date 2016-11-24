#pragma once
#include "learning_method.hpp"

namespace Convolutional::Learning {

	template<typename Classification>
	class Backpropagation : public ILearningMethod<Classification> {
	public:
		using ILearningMethod::ILearningMethod;

		auto BeginEpoch(typename networks_t::iterator network) -> void override {}
		auto EvaluateSet(typename networks_t::iterator network, typename TrainingData<Classification>::const_iterator set) -> void override {}
		auto EndEpoch(typename networks_t::iterator network) -> void override {}
	};

}