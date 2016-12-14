#include <stdlib.h>
#include <cstring>
#include <stdexcept>

#include "training/parameters.hpp"
#include "genotype/gene.hpp"
#include "utility/jsmn.h"
#include "utility/random.hpp"

using namespace Hippocrates;
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

std::ostream & Hippocrates::Genotype::operator«(std::ostream & stream, const Gene & gene)
{
	auto BoolToString = [](bool b) {
		return b ? "true" : "false";
	};
	stream << "{\"historicalMarking\":" <<
	std::to_string(gene.historicalMarking)<<
	",\"from\":"<<
	std::to_string(gene.from)<<
	",\"to\":"<<
	std::to_string(gene.to)<<
	",\"weight\":"<<
	std::to_string(gene.weight)<<
	",\"isEnabled\":"<<
	BoolToString(gene.isEnabled)<<
	",\"isRecursive\":"<<
	BoolToString(gene.isRecursive)<<
	"}";
	return stream;
}
