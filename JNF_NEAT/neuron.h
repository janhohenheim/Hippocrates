#pragma once
#include <cstddef>
#include <unordered_map>
#include <vector>

namespace JNF_NEAT {
	class NeuralNetwork;
	class Neuron {
		friend NeuralNetwork;
		public:
			struct IncomingConnection {
				Neuron* neuron = nullptr;
				float weight = 0.0f;
				bool isRecursive = false;
			};
		private:
			using Connections = std::vector<IncomingConnection>;
			Connections connections;
			float lastActionPotential = 0.0f;
			size_t layer = 0U;

		public:
			Neuron() = default;
			explicit Neuron(const Connections& connections);
			Neuron(const Neuron& other) = default;
			~Neuron() = default;

			void SetInput(float input);
			const Connections& GetConnections() const { return connections; }
			float RequestDataAndGetActionPotential();
			size_t GetLayer() const { return layer; }

		private:
			void AddConnection(IncomingConnection connection);
			void SetLayer(size_t layer);
			static float sigmoid(float d);
	};

}