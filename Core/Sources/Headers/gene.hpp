#pragma once
#include <cstddef>
#include <string>
#include "../Headers/utility.hpp"
#include "../Headers/type.hpp"

namespace Hippocrates {

struct Gene {
	Gene();
	explicit Gene(std::string json);
	Gene(const Gene& other) = default;
	Gene(Gene&& other) = default;
	~Gene() = default;

	auto operator=(const Gene& other) -> Gene& = default;
	auto operator=(Gene&& other) -> Gene& = default;
	auto operator==(const Gene& other) const -> bool;

	auto SetRandomWeight() -> void;
	auto GetJSON() const->std::string;

	std::size_t from = 0;
	std::size_t to = 0;
	Type::connection_weight_t weight = 0.0f;
	static constexpr auto invalidHistoricalMarking = std::numeric_limits<std::size_t>::max();
	std::size_t historicalMarking = invalidHistoricalMarking;
	bool isEnabled = true;
	bool isRecursive = false;
};

}
