#pragma once
#include "multi_matrix.hpp"
#include "interface.hpp"

#include <memory>

namespace Convolutional::Layer {

class ILayer : public Hippocrates::Utility::Interface {
public:
	using Hippocrates::Utility::Interface::Interface;

	virtual auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix = 0;

	virtual auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size = 0;
	virtual auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size = 0;
	virtual auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size = 0;

	virtual auto Clone() const noexcept -> std::unique_ptr<ILayer> = 0;
};

}
