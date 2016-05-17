#pragma once
#include <vector>
#include <cstddef>

class Neuron {
	public: 
		struct IncomingConnection {
			Neuron* incoming = nullptr;
			float weight = 1.0f;
		};
	private:
		using Connections = std::vector<IncomingConnection>;
		Connections connections;
		bool isSensor = false;
		float lastActionPotential = 0.0f;
		std::size_t layer;

    public:
        Neuron() = default;
		explicit Neuron(const Connections& connections);
		Neuron(const Neuron& other) = default;
        ~Neuron() = default;

		void SetInput(float input);
		void AddConnection(const IncomingConnection& connection);
		void AddConnection(IncomingConnection&& connection);
		const Connections& GetConnections() const {return connections;}
		Connections& GetConnections() {return connections;}
		float RequestDataAndGetActionPotential();
		void SetLayer(std::size_t layer);
		size_t GetLayer() const {return layer;}

	private:
		static float sigmoid(float d);
};