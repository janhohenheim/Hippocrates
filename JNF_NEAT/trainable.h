#pragma once
#include <vector>

class ITrainable
{
	public:
		virtual ~ITrainable() = default;

		virtual void Reset() = 0;
		virtual void Update(const std::vector<float>& networkOutputs) = 0;
		virtual int GetFitness() const = 0;

		virtual std::vector<float> ProvideNetworkWithInputs() const  = 0;
};