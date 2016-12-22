#pragma once
#include "multi_matrix.hpp"
#include "input_data/iinput_data.hpp"

namespace Convolutional {

class MultiMatrixFactory
{
public:
	static auto GetMultiMatrix(const InputData::IInputData& input) -> MultiMatrix;
};

}
