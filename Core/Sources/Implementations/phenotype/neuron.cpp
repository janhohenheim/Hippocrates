#include <cmath>
#include <stdexcept>

#include "phenotype/neuron.hpp"
#include "utility/jsmn.h"
#include "utility/random.hpp"

using namespace Hippocrates;
using namespace Hippocrates::Phenotype;

Neuron::Neuron(std::vector<Connection> connections) :
	connections(std::move(connections)) {
}

Neuron::Neuron(std::string json) {
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
	lastActionPotential = sigmoid(incomingPotentials);
	return lastActionPotential;
}

auto Neuron::sigmoid(Type::neuron_value_t d) -> Type::neuron_value_t {
	return tanh(d);
}

auto Neuron::SetInput(Type::neuron_value_t input) -> void {
	lastActionPotential = input;
}

void Neuron::Reset() {
	lastActionPotential = 0.0f;
}

std::ostream & Hippocrates::Phenotype::operator<<(std::ostream & stream, const Neuron & neuron)
{
	stream << "{\"layer\":" <<
	std::to_string(neuron.layer) <<
	"," <<
	"\"lastActionPotential\":" <<
	std::to_string(neuron.lastActionPotential) <<
	"}";
	return stream;
}
