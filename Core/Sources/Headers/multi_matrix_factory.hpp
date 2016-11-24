#pragma once
#include "multi_matrix.hpp"
#include "iinput_data.hpp"

namespace Convolutional {

class MultiMatrixFactory
{
public:
	static auto GetMultiMatrix(const InputData::IInputData& input) -> MultiMatrix;
};

}
