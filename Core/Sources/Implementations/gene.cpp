#include <stdlib.h>
#include <cstring>
#include <stdexcept>

#include "../Headers/gene.hpp"
#include "../Headers/jsmn.h"


using namespace Hippocrates;
using namespace std;

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
			sscanf(value.c_str(), "%zu", &historicalMarking);
		} else
		if (key == "to") {
			sscanf(value.c_str(), "%zu", &to);
		} else
		if (key == "weight") {
			weight = stof(value);
		} else
		if (key == "isEnabled") {
			isEnabled = value == "true";
		} else
		if (key == "isRecursive") {
			isRecursive = value == "true";
		}
	}
}

auto Gene::operator==(const Gene & other) const -> bool
{
	if (historicalMarking == other.historicalMarking
	 || (from == other.from
	    && to == other.to)) {
		if (isRecursive != other.isRecursive)
			throw std::logic_error("Two identical genes have different recursive flags");
		return true;
	}
	return false;
}

auto Gene::SetRandomWeight() -> void {
	weight = Utility::GetRandomNumberBetween(-8.0f, 8.0f);
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

