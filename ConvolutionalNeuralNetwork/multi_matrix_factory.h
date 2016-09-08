#pragma once
#include "multi_matrix.h"
#include "iinput_data.h"

namespace Convolutional {

class MultiMatrixFactory
{
public:
	static auto GetMultiMatrix(const InputData::IInputData& input) -> MultiMatrix;
};

}
