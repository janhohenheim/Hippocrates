#pragma once
#include <memory>

#include "training/parameters.hpp"

#include "possible_activation_functions.hpp"
#include "activation_function.hpp"
#include "tanh.hpp"
#include "fast_sigmoid.hpp"

namespace Hippocrates::ActivationFunction {

inline auto Create(PossibleActivationFunctions activationFunction) -> std::unique_ptr<IActivationFunction> {
	using Fun = PossibleActivationFunctions;
	switch (activationFunction) {
		case Fun::tanh: return std::make_unique<Tanh>();
		case Fun::fastSigmoid: return std::make_unique<FastSigmoid>();
		default: throw std::runtime_error("Tried to construct unsupported ActivationFunction");
	}
}

inline auto& GetFromParameters(){
		const auto& params = Training::GetParameters();
		const auto selectedFun = params.neural.activationFunction;
		static auto fun = Create(selectedFun);
		return *fun;
}

}