#pragma once
#include <cstddef>
#include <string>
#include "../Headers/utility.hpp"

namespace Hippocrates {

struct Gene {
private:
	static std::size_t numberOfExistingGenes;

public:
	Gene() = default;
	Gene(const Gene& other) = default;
	Gene(Gene&& other) = default;
	~Gene() = default;

	auto operator=(const Gene& other) -> Gene& = default;
	auto operator=(Gene&& other) -> Gene& = default;

	auto SetRandomWeight() -> void;
	auto GetJSON() const->std::string;

	std::size_t from = 0;
	std::size_t to = 0;
	float weight = Utility::GetRandomNumberBetween(-1.0f, 1.0f);
	std::size_t historicalMarking = numberOfExistingGenes++;
	bool isEnabled = true;
	bool isRecursive = false;
};

}
