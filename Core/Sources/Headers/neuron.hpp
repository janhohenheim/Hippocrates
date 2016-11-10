#pragma once
#include <cstddef>
#include <vector>
#include <string>

namespace Hippocrates {
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
	std::size_t layer = 0U;

public:
	Neuron() = default;
	explicit Neuron(std::vector<Connection> connections);
	Neuron(const Neuron& other) = default;
	Neuron(Neuron&& other) = default;
	Neuron(std::string json);
	~Neuron() = default;

	auto operator=(const Neuron& other) -> Neuron& = default;
	auto operator=(Neuron&& other) -> Neuron& = default;

	auto SetInput(float input) -> void;
	auto GetConnections() const -> const std::vector<Connection>& { return connections; }
	auto RequestDataAndGetActionPotential() -> float;
	auto GetLayer() const -> std::size_t { return layer; }
	auto GetJSON() const->std::string;

	auto Reset() -> void;

private:
	auto AddConnection(Connection connection) -> void;
	static auto sigmoid(float d) -> float;
};

}
