#pragma once
#include "ipooler.h"

namespace Convolutional {
namespace SubSampler {
namespace Pooler {

class MaxPooler : public IPooler {
public:
	auto ProcessMatrix(Matrix::Position position, const Matrix& net) const -> Matrix override;
	auto GetReceptiveField() const noexcept -> Matrix::Size override { return receptiveField; }
	auto GetZeroPadding() const noexcept -> Matrix::Size override { return zeroPadding; }
	auto GetStride() const noexcept -> Matrix::Size override { return stride; }

private:
	Matrix::Size receptiveField;
	Matrix::Size zeroPadding;
	Matrix::Size stride;
};

}
}
}
