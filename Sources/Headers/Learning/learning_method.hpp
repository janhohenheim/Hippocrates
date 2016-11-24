#pragma once
#include "neural_network.hpp"
#include "training_data.hpp"

namespace Convolutional::Learning {

	template<typename Classification>
	class ILearningMethod {
	public:
		using network_t = NeuralNetwork<Classification>;
		using networks_t = typename std::vector<network_t>;

		ILearningMethod(
			networks_t& neuralNetworks,
			const TrainingData<Classification>& data) 
			:
			neuralNetworks{ neuralNetworks.begin(), neuralNetworks.end() },
			data{data}	{}
		virtual ~ILearningMethod() = default;
		

		virtual auto IsFinished() const -> bool = 0;

		virtual auto BeginEpoch(typename networks_t::iterator network) -> void = 0;
		virtual auto EvaluateSet(typename networks_t::iterator network, typename TrainingData<Classification>::const_iterator set) -> void = 0;
		virtual auto EndEpoch(typename networks_t::iterator network) -> void = 0;

		virtual auto GetChamp() const -> typename network_t = 0;

	protected:
		std::vector<std::reference_wrapper<network_t>> neuralNetworks;
		const TrainingData<Classification>& data;
	};

}