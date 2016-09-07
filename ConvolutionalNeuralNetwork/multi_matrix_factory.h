#pragma once
#include "multi_dimensional_matrix.h"
#include "iinput_data.h"

namespace Convolutional {

class MultiMatrixFactory
{
public:
	static auto GetMultiMatrix(const InputData::IInputData& input) -> MultiDimensionalMatrix;
};

}
