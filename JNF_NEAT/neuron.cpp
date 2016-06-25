#include "neuron.h"
#include <cmath>
#include <stdexcept>
#include <string>

using namespace JNF_NEAT;
using namespace std;

Neuron::Neuron(vector<Connection> connections) :
connections(std::move(connections)) {
}

void Neuron::AddConnection(Connection connection) {
	if (connection.neuron == this || connection.neuron == nullptr) {
		throw invalid_argument("Invalid incoming connection");
	}
	connections.push_back(move(connection));
}

float Neuron::RequestDataAndGetActionPotential() {
	float incomingPotentials = 0.0f;
	for (auto& in : connections){
		if (!in.outGoing) {
			incomingPotentials += in.neuron->lastActionPotential * in.weight;
		}
	}
	lastActionPotential = sigmoid(incomingPotentials);
	return lastActionPotential;
}

float Neuron::sigmoid(float d) {
	return tanh(d);
}

void Neuron::SetInput(float input) {
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

