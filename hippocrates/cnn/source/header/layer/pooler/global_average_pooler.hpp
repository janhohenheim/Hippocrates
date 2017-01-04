#pragma once
#include "layer/pooler/ipooler.hpp"

namespace Convolutional::Layer::Pooler {

	class GlobalAveragePooler : public IPooler {
	public:
		using IPooler::IPooler;

		auto ProcessMultiMatrix(const MultiMatrix& multiMatrix)->MultiMatrix override;

		auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return size; }
		auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return {0, 0}; }
		auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }

		auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<GlobalAveragePooler>(*this); }


		auto ProcessMatrix(const Matrix& matrix) const -> Matrix::element_t;
	};

}
