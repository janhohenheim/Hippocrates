#pragma once
#include "Layer/Pooler/ipooler.hpp"

namespace Convolutional::Layer::Pooler {

class MaxPooler : public IPooler {
public:
	auto ProcessMatrix(Matrix matrix) const -> Matrix override;
	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return {2, 2}; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return {0, 0}; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return GetReceptiveField(size); }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> { return std::make_unique<MaxPooler>(*this); }
};

}
