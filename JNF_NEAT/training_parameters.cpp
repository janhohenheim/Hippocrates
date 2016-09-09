#include "training_parameters.h"
using namespace JNF_NEAT;
using namespace std;

auto TrainingParameters::GetJSON() const -> std::string {
	string s("{");
	s += "\"numberOfInputs\":";
	s += to_string(numberOfInputs);
	s += ",\"numberOfOutputs\":";
	s += to_string(numberOfOutputs);

	s += ",\"advanced\":";
	s += "{";

	s += ",\"ranges\":";
	s += "{";
	s += ",\"minWeight\":";
	s += to_string(advanced.ranges.minWeight);
	s += ",\"maxWeight\":";
	s += to_string(advanced.ranges.maxWeight);
	s += "}";
	// etc.
	// Todo sara: append the rest of the members to the string

	s += "}";

	s += "}";

	return s;
}