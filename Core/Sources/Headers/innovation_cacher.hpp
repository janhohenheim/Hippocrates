#pragma once
#include <vector>
#include <type_traits>
#include "genome.hpp"

namespace Hippocrates {

class InnovationCacher {
public:
	auto AssignAndCacheHistoricalMarkings(Genome& genome) -> void;
	auto AssignAndCacheHistoricalMarking(Gene& gene) -> void;
	auto Clear() -> void;

private:
	std::vector<Gene> cache;
	using cache_iterator = decltype(cache)::iterator;
	std::size_t nextHighestHistoricalMarking = 0;

private:
	auto GetAndIncrementNextHighestHistoricalMarking() -> std::size_t;
	auto FindGeneInCache(const Gene& gene) -> cache_iterator;
};

}