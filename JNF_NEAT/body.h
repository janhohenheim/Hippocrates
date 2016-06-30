#pragma once
#include <vector>

namespace JNF_NEAT {

	class IBody	{
		public:
			IBody() = default;
			IBody(const IBody&) = default;
			IBody(IBody&&) = default;
			IBody& operator=(const IBody&)& = default;
			IBody& operator=(IBody&&)& = default;
			virtual ~IBody() = default;

			virtual void Reset() = 0;
			virtual void Update(const std::vector<float>& networkOutputs) = 0;
			virtual double GetFitness() const = 0;

			virtual std::vector<float> ProvideNetworkWithInputs() const = 0;
	};

}