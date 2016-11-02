#include <stdlib.h>
#include "../Headers/gene.hpp"


using namespace Hippocrates;
using namespace std;

size_t Gene::numberOfExistingGenes = 0U;

auto Gene::SetRandomWeight() -> void {
	weight = Utility::GetRandomNumberBetween(-1.0f, 1.0f);
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

