#include <cmath>
#include <stdexcept>
#include "../Headers/neuron.h"

using namespace Hippocrates;
using namespace std;

Neuron::Neuron(vector<Connection> connections) :
	connections(std::move(connections)) {
}

auto Neuron::AddConnection(Connection connection) -> void {
	if (connection.neuron == this || connection.neuron == nullptr) {
		throw invalid_argument("Invalid incoming connection");
	}
	connections.push_back(move(connection));
}

auto Neuron::RequestDataAndGetActionPotential() -> float {
	float incomingPotentials = 0.0f;
	for (auto& in : connections) {
		if (!in.outGoing) {
			incomingPotentials += in.neuron->lastActionPotential * in.weight;
		}
	}
	lastActionPotential = sigmoid(incomingPotentials);
	return lastActionPotential;
}

auto Neuron::sigmoid(float d) -> float {
	return tanh(d);
}

auto Neuron::SetInput(float input) -> void {
	lastActionPotential = input;
}


string Neuron::GetJSON() const {
	string s("{\"layer\":");
	s += to_string(layer);
	s += ",";
	s += "\"lastActionPotential\":";
	s += to_string(lastActionPotential);
	s += "}";
	return s;
}

void Neuron::Reset() {
	lastActionPotential = 0.0f;
}
