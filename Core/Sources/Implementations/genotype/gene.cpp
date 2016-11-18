#include <stdlib.h>
#include <cstring>
#include <stdexcept>

#include "../../Headers/genotype/gene.hpp"
#include "../../Headers/utility/jsmn.h"
#include "../../Headers/type.hpp"
#include "../../Headers/training/parameters.hpp"
#include "../../Headers/utility/random.hpp"

using namespace Hippocrates::Genotype;

Gene::Gene() {
	SetRandomWeight();
}

Gene::Gene(std::string json) {
	jsmn_parser parser;
	jsmn_init(&parser);
	jsmntok_t tokens[256];

	std::size_t token_count = jsmn_parse(&parser, json.c_str(), json.length(), tokens, 256);

	for (std::size_t i = 0; i < token_count - 1; i++) {
		auto key = json.substr(tokens[i].start, tokens[i].end - tokens[i].start);
		auto value = json.substr(tokens[i + 1].start, tokens[i + 1].end - tokens[i + 1].start);

		if (key == "historicalMarking") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &historicalMarking);
		} else
		if (key == "to") {
			HIPPOCRATES_SSCANF(value.c_str(), "%zu", &to);
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
	weight = Utility::Random::Number(Training::GetParameters().ranges.minWeight, Training::GetParameters().ranges.maxWeight);
}

auto Gene::GetJSON() const -> std::string {
	auto BoolToString = [](bool b) {
		return b ? "true" : "false";
	};
	std::string s("{\"historicalMarking\":");
	s += std::to_string(historicalMarking);
	s += ",\"from\":";
	s += std::to_string(from);
	s += ",\"to\":";
	s += std::to_string(to);
	s += ",\"weight\":";
	s += std::to_string(weight);
	s += ",\"isEnabled\":";
	s += BoolToString(isEnabled);
	s += ",\"isRecursive\":";
	s += BoolToString(isRecursive);
	s += "}";
	return s;
}

