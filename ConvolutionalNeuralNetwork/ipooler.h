#pragma once
#include "matrix.h"

namespace Convolutional {

class IPooler {
public:
	virtual auto Pool(Matrix::Position position, const Matrix& net) const -> Matrix = 0;
};

}