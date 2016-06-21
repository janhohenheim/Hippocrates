#include "neuron.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

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


void Neuron::ExportJSON(ostream& output) const {
	stringstream s;
	s << "{\"layer\":" << layer << ","
		<< "\"lastActionPotential\":" << lastActionPotential << "}";
	output << s.rdbuf();
}

