#pragma once
#include <vector>
#include <memory>
#include "iinput_data.hpp"
#include "multi_matrix.hpp"
#include "multi_matrix_factory.hpp"

namespace Convolutional {

template <typename Classification>
class TrainingData {
public:
	struct CategorizedData {
	    CategorizedData(
			MultiMatrix multiMatrix, 
			Classification classification)
	        : 
			multiMatrix{std::move(multiMatrix)},	          
			classification{std::move(classification)} {   }

		MultiMatrix multiMatrix;
		Classification classification;
	};

	using const_iterator = typename std::vector<CategorizedData>::const_iterator;

public:

	TrainingData() = default;
	explicit TrainingData(std::vector<CategorizedData> categorizedData) : categorizedData(std::move(categorizedData)) {};
	
	template <typename DataType>
	auto AddData(const DataType& input, Classification classification) {
		static_assert(
			std::is_base_of<InputData::IInputData, DataType>::value,
			"DataType must be a descendant of IInputData"
		);
		MultiMatrix multiMatrix{MultiMatrixFactory::GetMultiMatrix(input)};
		AddData({ std::move(multiMatrix), classification });
	}

	auto AddData(CategorizedData data) { categorizedData.push_back(std::move(data)); }

	auto begin() const noexcept { return categorizedData.begin(); }
	auto end() const noexcept { return categorizedData.end(); }

private:
	std::vector<CategorizedData> categorizedData;
};

}
