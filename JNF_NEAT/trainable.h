#pragma once
#include <vector>

class ITrainable
{
	public:
		virtual ~ITrainable() = default;

		virtual void Reset() = 0;
		virtual void Update() = 0;
		virtual int GetOrCalculateFitness() = 0;

		virtual void ReceiveNetworkOutputs(std::vector<float>) = 0;
		virtual std::vector<float> ProvideNetworkWithInputs() = 0;
};