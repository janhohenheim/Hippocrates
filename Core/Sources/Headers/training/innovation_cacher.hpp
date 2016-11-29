#pragma once
#include <vector>
#include "genotype/genome.hpp"
#include "genotype/gene.hpp"

namespace Hippocrates::Training {

class InnovationCacher {
public:
	auto AssignAndCacheHistoricalMarkings(Genotype::Genome& genome) -> void;
	auto AssignAndCacheHistoricalMarking(Genotype::Gene& gene) -> void;
	auto Clear() -> void;

private:
	std::vector<Genotype::Gene> cache;
	using cache_iterator = decltype(cache)::iterator;
	std::size_t nextHighestHistoricalMarking = 0;

private:
	auto GetAndIncrementNextHighestHistoricalMarking() -> std::size_t;
	auto FindGeneInCache(const Genotype::Gene& gene) -> cache_iterator;
};

}