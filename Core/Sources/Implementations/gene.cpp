#include <stdlib.h>
#include <cstring>
#include "../Headers/gene.hpp"
#include "../Headers/jsmn.h"

using namespace Hippocrates;
using namespace std;

size_t Gene::numberOfExistingGenes = 0U;

Gene::Gene() {
	SetRandomWeight();
}

Gene::Gene(std::string json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	auto token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (size_t i = 0; i < token_count - 1; i++) {
		auto key = json.substr(tokens[i].start, tokens[i].end - tokens[i].start);
		auto value = json.substr(tokens[i + 1].start, tokens[i + 1].end - tokens[i + 1].start);

		if (key == "historicalMarking") {
			historicalMarking = stoul(value);
		}

		if (key == "to") {
			to = stoul(value);
		}

		if (key == "weight") {
			weight = stof(value);
		}

		if (key == "isEnabled") {
			isEnabled = value == "true";
		}

		if (key == "isRecursive") {
			isRecursive = value == "true";
		}
	}
}

auto Gene::SetRandomWeight() -> void {
	/*
	const auto& min = parameters.ranges.minWeight;
	const auto& max = parameters.ranges.maxWeight;
	if (min == max) {
	weight = min;
	}
	else {
	weight = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	}
	*/
	weight = (float)(rand() % 10'000) / 9'999.0f;
	if (rand() % 2) {
		weight = -weight;
	}
}

auto Gene::GetJSON() const -> string {
	auto BoolToString = [](bool b) {
		return b ? "true" : "false";
	};
	string s("{\"historicalMarking\":");
	s += to_string(historicalMarking);
	s += ",\"from\":";
	s += to_string(from);
	s += ",\"to\":";
	s += to_string(to);
	s += ",\"weight\":";
	s += to_string(weight);
	s += ",\"isEnabled\":";
	s += BoolToString(isEnabled);
	s += ",\"isRecursive\":";
	s += BoolToString(isRecursive);
	s += "}";
	return s;
}

