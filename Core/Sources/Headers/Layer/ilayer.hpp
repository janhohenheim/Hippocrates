#pragma once
#include "multi_matrix.hpp"
#include <memory>

namespace Convolutional::Layer {

class ILayer {
public:
	virtual auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) const -> MultiMatrix final;

	virtual auto ProcessMatrix(Matrix::Position position, const Matrix& net) const -> Matrix = 0;
	virtual auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size = 0;
	virtual auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size = 0;
	virtual auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size = 0;

	virtual auto Clone() const noexcept -> std::unique_ptr<ILayer> = 0;
};

}
