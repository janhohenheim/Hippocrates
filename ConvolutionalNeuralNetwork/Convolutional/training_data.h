#pragma once
#include <vector>
#include <memory>
#include "InputData/iinput_data.h"
#include "multi_matrix.h"
#include "multi_matrix_factory.h"

namespace Convolutional {

template <typename Classification>
class TrainingData {
public:
	struct CategorizedData {		
		MultiMatrix multiMatrix;
		Classification classification;
	};
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
