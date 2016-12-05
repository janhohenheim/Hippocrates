#include <stdexcept>

#include "phenotype/neuron.hpp"
#include "utility/jsmn.h"
#include "utility/random.hpp"
#include "activation_function/tanh.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Phenotype;

Neuron::Neuron(std::vector<Connection> connections) :
	connections(std::move(connections)) {
}

Neuron::Neuron(const std::string& json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	std::size_t token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (std::size_t i = 0; i < token_count - 1; i++) {
		auto key = json.substr(tokens[i].start, tokens[i].end - tokens[i].start);
		auto value = json.substr(tokens[i + 1].start, tokens[i + 1].end - tokens[i + 1].start);

		if (key == "lastActionPotential") {
			lastActionPotential = stof(value);
		} else
		if (key == "layer") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &layer);
		}
	}
}

auto Neuron::AddConnection(Connection connection) -> void {
	if (connection.neuron == this || connection.neuron == nullptr) {
		throw std::invalid_argument("Invalid incoming connection");
	}
	connections.push_back(std::move(connection));
}

auto Neuron::RequestDataAndGetActionPotential() -> Type::neuron_value_t {
	Type::neuron_value_t incomingPotentials = 0.0f;
	for (auto& in : connections) {
		if (!in.outGoing) {
			incomingPotentials += in.neuron->lastActionPotential * in.weight;
		}
	}
	return lastActionPotential = activationFunction(incomingPotentials);
}


auto Neuron::SetInput(Type::neuron_value_t input) -> void {
	lastActionPotential = input;
}

std::string Neuron::GetJSON() const {
	std::string s("{\"layer\":");
	s += std::to_string(layer);
	s += ",";
	s += "\"lastActionPotential\":";
	s += std::to_string(lastActionPotential);
	s += "}";
	return s;
}

void Neuron::Reset() {
	lastActionPotential = 0.0f;
}
