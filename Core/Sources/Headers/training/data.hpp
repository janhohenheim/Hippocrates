#pragma once
#include <vector>
#include <algorithm>
#include "phenotype/neural_network.hpp"

namespace Hippocrates::Training {

template <typename Classification, std::size_t ClassificationCount = static_cast<std::size_t>(Classification::ClassificationCount)>
class Data {
public:
	struct Set {
		Type::neuron_values_t input;
		Classification classification;
	};
	using const_iterator = typename std::vector<Set>::const_iterator;

public:
	Data() = default;
	explicit Data(std::vector<Set> categorizedData) 
		: 
		sets(std::move(categorizedData)) 
	{
		auto GetSetWithHigherInput = [&](const Set& lhs, const Set& rhs) {return GetMaxInputInSet(lhs) < GetMaxInputInSet(rhs); };
		auto GetSetWithLowerInput = [&](const Set& lhs, const Set& rhs) {return GetMinInputInSet(lhs) < GetMinInputInSet(rhs); };
		highestInput = *std::max_element(sets.begin(), sets.end(), GetSetWithHigherInput);
		lowestInput = *std::min_element(sets.begin(), sets.end(), GetSetWithLowerInput);
	}
	
	auto AddSet(Set data) { 
		sets.push_back(std::move(data)); 
		UpdateRangesForLastElement(); 
	}

	template<typename U = Type::neuron_values_t, class = typename std::enable_if<std::is_constructible<U, std::initializer_list<typename U::value_type>>::value, bool>::type>
	auto AddSet(std::initializer_list<typename U::value_type> input, Classification&& classification) {
		Set set;
		Type::neuron_values_t formattedInput(std::move(input.begin()), std::move(input.end()));
		set.input = std::move(formattedInput);
		set.classification = std::forward<Classification>(classification);
		sets.push_back(std::move(set));

		UpdateRangesForLastElement();
	}

	auto GetSize() const { return sets.size(); }

	auto operator[](std::size_t index) const { 
		Set set = sets[index];
		for (auto& in : set.input) {
			const auto normalIn = Normalize(in, lowestInput, highestInput);
			const auto scaledIn = ScaleInRange(normalIn, GetParameters().ranges.minWeight, GetParameters().ranges.maxWeight);
			in = scaledIn;
		}
		return set;
	}
	auto At(std::size_t index) const { return operator[](index); }


private:
	auto UpdateRangesForLastElement() {
		const auto highestNewInput = GetMaxInputInSet(sets.back());
		const auto lowestNewInput = GetMinInputInSet(sets.back());
		highestInput = std::max(highestInput, highestNewInput);
		lowestInput = std::min(lowestInput, lowestNewInput);
	}

	template <typename T>
	static inline auto Normalize(T x, T xMin, T xMax) {
		return (x - xMin) / (xMax - xMin);
	}

	template <typename T>
	static inline auto ScaleInRange(T x, T lowerBound, T upperBound) {
		return x * (upperBound - lowerBound) + lowerBound;
	}

	auto GetMaxInputInSet(const Set& set) const { return *std::max_element(set.input.begin(), set.input.end()); }
	auto GetMinInputInSet(const Set& set) const { return *std::min_element(set.input.begin(), set.input.end()); }
private:
	std::vector<Set> sets;
	Type::neuron_value_t lowestInput = 0;
	Type::neuron_value_t highestInput = 0;

};

}
