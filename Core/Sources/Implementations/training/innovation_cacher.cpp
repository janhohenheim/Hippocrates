#include "../../Headers/training/innovation_cacher.hpp"
#include <algorithm>

using namespace Hippocrates::Training;

auto InnovationCacher::AssignAndCacheHistoricalMarkings(Genotype::Genome & genome) -> void {
	for (auto& gene: genome)
		AssignAndCacheHistoricalMarking(gene);
}

auto InnovationCacher::AssignAndCacheHistoricalMarking(Genotype::Gene & gene) -> void {
	const auto cachedInnovation = FindGeneInCache(gene);
	if (cachedInnovation == cache.end()) {
		gene.historicalMarking = GetAndIncrementNextHighestHistoricalMarking();
		cache.push_back(gene);
	}
	else {
		gene.historicalMarking = cachedInnovation->historicalMarking;
	}
}

auto InnovationCacher::Clear() -> void {
	cache.clear();
}

auto InnovationCacher::GetAndIncrementNextHighestHistoricalMarking() -> std::size_t {
	return nextHighestHistoricalMarking++;
}

auto InnovationCacher::FindGeneInCache(const Genotype::Gene & gene) -> cache_iterator {
	return std::find(cache.begin(), cache.end(), gene);
}
