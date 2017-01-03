#pragma once
#include "layer/pooler/ipooler.hpp"

namespace Convolutional::Layer::Pooler {

	class GlobalAveragePooler : public IPooler {
	public:
		using IPooler::IPooler;

		GlobalAveragePooler(Matrix::Size receptiveField = { 2, 2 },
			Matrix::Size stride = { 2, 2 })
			: receptiveField(receptiveField),
			stride(stride)
		{ }
		GlobalAveragePooler(const GlobalAveragePooler&) = default;
		GlobalAveragePooler(GlobalAveragePooler&&) = default;

		auto ProcessMultiMatrix(const MultiMatrix& multiMatrix)->MultiMatrix override;

		auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return receptiveField; }
		auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return { 0, 0 }; }
		auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return stride; }

		auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<GlobalAveragePooler>(*this); }


		auto ProcessMatrix(const Matrix& matrix) const->Matrix::element_t;
		auto GetSizeAfterPooling(Matrix::Size originalSize) const->Matrix::Size;

	private:
		Matrix::Size receptiveField;
		Matrix::Size stride;
	};

}
