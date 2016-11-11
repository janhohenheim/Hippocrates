#include <cmath>
#include <stdexcept>
#include "../Headers/neuron.hpp"
#include "../Headers/jsmn.h"

using namespace Hippocrates;
using namespace std;

Neuron::Neuron(vector<Connection> connections) :
	connections(std::move(connections)) {
}

Neuron::Neuron(std::string json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	auto token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (size_t i = 0; i < token_count - 1; i++) {
		auto key = json.substr(tokens[i].start, tokens[i].end - tokens[i].start);
		auto value = json.substr(tokens[i + 1].start, tokens[i + 1].end - tokens[i + 1].start);

		if (key == "lastActionPotential") {
			lastActionPotential = stof(value);
		} else
		if (key == "layer") {
			sscanf(value.c_str(), "%zu", &layer);
		}
	}
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
