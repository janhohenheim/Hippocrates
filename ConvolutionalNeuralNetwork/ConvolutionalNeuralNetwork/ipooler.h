#pragma once
#include "matrix.h"

namespace Convolutional {

class IPooler {
public:
	virtual auto Pool(const Matrix& net) const -> Matrix = 0;
};

}