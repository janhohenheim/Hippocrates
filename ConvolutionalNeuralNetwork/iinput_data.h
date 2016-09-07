#pragma once
#include "multi_dimensional_matrix.h"

namespace Convolutional {
namespace InputData {

class IInputData {
public:
	virtual auto GetMultiDimensionalMatrix() const -> MultiDimensionalMatrix = 0;
};

}
}
