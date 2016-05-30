#pragma once
#include <cstddef>
#include <unordered_map>

class Neuron {
	private:
		struct IncomingConnection {
			Neuron* neuron = nullptr;
			float weight = 0.0f;
		};
		using Connections = std::vector<IncomingConnection>;
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
		bool IsSensor() const { return isSensor; }
		void AddConnection(IncomingConnection&& connection);
		const Connections& GetConnections() const {return connections;}
		Connections& GetConnections() {return connections;}
		float RequestDataAndGetActionPotential();
		size_t GetLayer() const {return layer; }
		void SetLayer(size_t layer);

	private:
		static float sigmoid(float d);
};