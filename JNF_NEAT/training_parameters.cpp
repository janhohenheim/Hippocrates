#include "training_parameters.h"
using namespace JNF_NEAT;
using namespace std;

auto TrainingParameters::GetJSON() const -> std::string {
	string s("{");

	s += ",\"ranges\":";
	s += "{";
	s += ",\"minWeight\":";
	s += to_string(ranges.minWeight);
	s += ",\"maxWeight\":";
	s += to_string(ranges.maxWeight);
	s += "}";
	// etc.
	// Todo sara: append the rest of the members to the string

	s += "}";

	return s;
}
