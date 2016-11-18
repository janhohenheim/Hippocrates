#pragma once
#include <vector>

namespace Hippocrates::Type {

#ifdef _WIN32
#define HIPPOCRATES_SSCANF sscanf_s
#else
#define HIPPOCRATES_SSCANF sscanf
#endif

using connection_weight_t = float;
using neuron_value_t = float;
using neuron_values_t = std::vector<neuron_value_t>;
using fitness_t = double;

}
