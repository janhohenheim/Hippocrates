#pragma once
#include <vector>
namespace JNF_NEAT {

template <typename InputType, typename Classification, std::size_t ClassificationCount = static_cast<std::size_t>(Classification::ClassificationCount)>
class TrainingData {
public:
	struct Set {
		InputType input;
		Classification classification;
	};
	using const_iterator = typename std::vector<Set>::const_iterator;

public:
	TrainingData() = default;
	explicit TrainingData(std::vector<Set> categorizedData) : sets(std::move(categorizedData)) {};
	
	auto AddSet(Set data) { sets.push_back(std::move(data)); }

	auto GetSize() const { return sets.size(); }

	auto begin() const noexcept { return sets.begin(); }
	auto end() const noexcept { return sets.end(); }

private:
	std::vector<Set> sets;


};

}
