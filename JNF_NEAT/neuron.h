#pragma once
#include <cstddef>
#include <unordered_map>

class Neuron {
	private:
        struct IncommingConnection {
            Neuron* neuron;
            float weight;
        };
		using Connections = std::vector<IncommingConnection>;
		Connections connections;
		bool isSensor = false;
		float lastActionPotential = 0.0f;
		size_t layer = 0U;

    public:
        Neuron() = default;
		explicit Neuron(const Connections& connections);
		Neuron(const Neuron& other) = default;
        ~Neuron() = default;

		void SetInput(float input);
		void AddConnection(IncommingConnection&& connection);
		const Connections& GetConnections() const {return connections;}
		Connections& GetConnections() {return connections;}
		float RequestDataAndGetActionPotential();
		size_t GetLayer() const {return layer; }
		void SetLayer(size_t layer);

	private:
		static float sigmoid(float d);
};