#pragma once
#include <vector>
#include "../phenotype/neural_network.hpp"

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
	explicit Data(std::vector<Set> categorizedData) : sets(std::move(categorizedData)) {};
	
	auto AddSet(Set data) { sets.push_back(std::move(data)); }
	template<typename U = Type::neuron_values_t, class = typename std::enable_if<std::is_constructible<U, std::initializer_list<typename U::value_type>>::value, bool>::type>
	auto AddSet(std::initializer_list<typename U::value_type> input, Classification&& classification) {
		Set set;
		Type::neuron_values_t formattedInput(std::move(input.begin()), std::move(input.end()));
		set.input = std::move(formattedInput);
		set.classification = std::forward<Classification>(classification);
		sets.push_back(std::move(set));
	}

	auto GetSize() const { return sets.size(); }

	auto begin() const noexcept { return sets.begin(); }
	auto end() const noexcept { return sets.end(); }

private:
	std::vector<Set> sets;


};

}
