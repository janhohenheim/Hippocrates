#pragma once
#include <cstddef>
#include <vector>
#include <string>

namespace JNF_NEAT {
	class NeuralNetwork;
	class Neuron {
		friend NeuralNetwork;
		public:
			struct Connection {
				Neuron* neuron = nullptr;
				float weight = 0.0f;
				bool isRecursive = false;
				bool outGoing = false;
			};
		private:
			std::vector<Connection> connections;
			float lastActionPotential = 0.0f;
			size_t layer = 0U;

		public:
			Neuron() = default;
			explicit Neuron(std::vector<Connection> connections);
			Neuron(const Neuron& other) = default;
			Neuron(Neuron&& other) = default;
			~Neuron() = default;
			Neuron& operator=(const Neuron& other) = default;
			Neuron& operator=(Neuron&& other) = default;

			void SetInput(float input);
			const std::vector<Connection>& GetConnections() const { return connections; }
			float RequestDataAndGetActionPotential();
			size_t GetLayer() const { return layer; }
			std::string GetJSON() const;

		private:
			void AddConnection(Connection connection);
			static float sigmoid(float d);
	};

}