#pragma once
#include "../multi_matrix.hpp"

namespace Convolutional {
namespace SubSampler {

class ISubSampler {
public:
	virtual auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) const -> MultiMatrix final;

	virtual auto ProcessMatrix(Matrix::Position position, const Matrix& net) const -> Matrix = 0;
	virtual auto GetReceptiveField() const noexcept -> Matrix::Size = 0;
	virtual auto GetZeroPadding() const noexcept -> Matrix::Size = 0;
	virtual auto GetStride() const noexcept -> Matrix::Size = 0;
};

}
}
