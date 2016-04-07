#pragma once
#include <vector>

class Neuron {
	public: 
		struct IncomingConnection {
			Neuron * incoming;
			float weight = 1.0f;
		};
	private:
		using Connections = std::vector<IncomingConnection>;
		Connections connections;

    public:
        Neuron() = default;
		explicit Neuron(const Connections & connections);
        Neuron(const Neuron & other) = default;
        ~Neuron() = default;

		void AddConnection(IncomingConnection connection);
		float RequestDataAndGetActionPotential();

	private:
		static float sigmoid(float d);
};