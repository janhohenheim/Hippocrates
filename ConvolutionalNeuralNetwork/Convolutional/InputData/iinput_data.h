#pragma once
#include "../multi_matrix.h"

namespace Convolutional {
namespace InputData {

class IInputData {
public:
	virtual auto GetMultiDimensionalMatrix() const -> MultiMatrix = 0;
};

}
}
