#pragma once
#include <vector>

class Neuron {
	public: 
		struct IncomingConnection {
			Neuron * incoming = nullptr;
			float weight = 1.0f;
		};
	private:
		using Connections = std::vector<IncomingConnection>;
		Connections connections;
		bool isSensor = false;
		float lastActionPotential = 0.0;

    public:
        Neuron() = default;
		explicit Neuron(const Connections & connections);
        Neuron(const Neuron & other) = default;
        ~Neuron() = default;

		void SetInput(float input);
		void AddConnection(const IncomingConnection & connection);
		void AddConnection(IncomingConnection &&connection);
		float RequestDataAndGetActionPotential();

	private:
		static float sigmoid(float d);
};