#pragma once
#include "ipooler.hpp"

namespace Convolutional {
namespace Layer {
namespace Pooler {

class MaxPooler : public IPooler {
public:
	auto ProcessMatrix(Matrix::Position position, const Matrix& matrix) const -> Matrix override;
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
