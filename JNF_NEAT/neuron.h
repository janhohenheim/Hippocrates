#pragma once
#include <map>
#include <cstddef>

class Neuron {
	private:
		using Connections = std::map<Neuron*, float>;
		Connections connections;
		bool isSensor = false;
		float lastActionPotential = 0.0f;
		std::size_t distanceFromOutput;

    public:
        Neuron() = default;
		explicit Neuron(const Connections& connections);
		Neuron(const Neuron& other) = default;
        ~Neuron() = default;

		void SetInput(float input);
		void AddConnection(Neuron* incoming, float weight);
		const Connections& GetConnections() const {return connections;}
		Connections& GetConnections() {return connections;}
		float RequestDataAndGetActionPotential();
		void SetDistanceFromOutput(std::size_t distanceFromOutput);
		size_t GetDistanceFromOutput() const {return distanceFromOutput;}

	private:
		static float sigmoid(float d);
};