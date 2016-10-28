#pragma once
#include "../multi_matrix.hpp"

namespace Convolutional {
namespace InputData {

class IInputData {
public:
	virtual auto GetMultiDimensionalMatrix() const -> MultiMatrix = 0;
};

}
}
