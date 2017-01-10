#pragma once
#include "layer/pooler/ipooler.hpp"
#include "matrix_view.hpp"

namespace Convolutional::Layer::Pooler {

class MaxPooler : public IPooler {
public:
	using IPooler::IPooler;

	MaxPooler(Matrix::Size receptiveField = {2, 2},
			Matrix::Size stride = {2, 2})
	:	receptiveField(receptiveField),
		stride(stride)
	{ }
	MaxPooler(const MaxPooler&) = default;
	MaxPooler(MaxPooler&&) = default;

	auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;

	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return receptiveField; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return {0, 0}; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return stride; }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<MaxPooler>(*this); }


	auto ProcessSubmatrix(const MatrixView& matrix) const -> Matrix::element_t;

private:
	Matrix::Size receptiveField;
	Matrix::Size stride;
};

}
