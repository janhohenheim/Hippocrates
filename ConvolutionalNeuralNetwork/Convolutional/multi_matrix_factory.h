#pragma once
#include "multi_matrix.h"
#include "InputData/iinput_data.h"

namespace Convolutional {

class MultiMatrixFactory
{
public:
	static auto GetMultiMatrix(const InputData::IInputData& input) -> MultiMatrix;
};

}
