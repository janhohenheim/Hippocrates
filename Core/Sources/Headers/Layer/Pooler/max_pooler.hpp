#pragma once
#include "Layer/Pooler/ipooler.hpp"

namespace Convolutional::Layer::Pooler {

class MaxPooler : public IPooler {
public:
	auto ProcessMatrix(Matrix::Position position, const Matrix& matrix) const -> Matrix override;
	auto GetReceptiveField() const noexcept -> Matrix::Size override { return receptiveField; }
	auto GetZeroPadding() const noexcept -> Matrix::Size override { return zeroPadding; }
	auto GetStride() const noexcept -> Matrix::Size override { return stride; }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> { return std::make_unique<MaxPooler>(*this); }

private:
	Matrix::Size receptiveField;
	Matrix::Size zeroPadding;
	Matrix::Size stride;
};

}
