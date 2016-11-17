#include "../Headers/innovation_cacher.hpp"
using namespace Hippocrates;

auto Hippocrates::InnovationCacher::AssignAndCacheHistoricalMarkings(Genome & genome) -> void {
	for (auto& gene: genome)
		AssignAndCacheHistoricalMarking(gene);
}

auto InnovationCacher::AssignAndCacheHistoricalMarking(Gene & gene) -> void {
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

auto InnovationCacher::FindGeneInCache(const Gene & gene) -> cache_iterator {
	return std::find(cache.begin(), cache.end(), gene);
}
