#pragma once
#include <vector>

class Neuron {
	public: 
		struct IncomingConnection {
			Neuron * incoming;
			float weight = 1.0f;
		};
	private:
		// TODO jnf
		// Rename this
		using in = std::vector<IncomingConnection>;
		in connections;

    public:
        Neuron() = default;
		explicit Neuron(const in & connections);
        Neuron(const Neuron & other) = default;
        ~Neuron() = default;

		void AddConnection(IncomingConnection connection);
		float RequestDataAndGetActionPotential();

	private:
		static float sigmoid(float d);
};