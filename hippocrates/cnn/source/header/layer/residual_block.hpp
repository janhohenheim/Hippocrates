#pragma once
#include "matrix.hpp"
#include "ilayer.hpp"
#include "random.hpp"
#include "layers.hpp"
#include <memory>

namespace Convolutional::Layer {

class ResidualBlock : public ILayer {
public:
	using ILayer::ILayer;

	ResidualBlock(
		std::size_t convolutionCount,
		std::size_t dimensionCount,
		Matrix::Size receptiveField = {3, 3},
		Matrix::Size stride = {1, 1})
		:
		receptiveField{std::move(receptiveField)},
		stride{std::move(stride)}
	{
		std::vector<Layers::Layer_t> layers;
		layers.reserve(convolutionCount*2 );

		const Filter filter{this->receptiveField, this->stride};
		const Convolution convolution{dimensionCount, filter};
		for (std::size_t i = 0; i < convolutionCount; ++i) {
			layers.push_back(std::make_unique<Convolution>(convolution));
			layers.push_back(std::make_unique<ReLU>());
		}

		this->layers = Layers{std::move(layers)};
	}

	ResidualBlock(const ResidualBlock& other) = default;
	ResidualBlock(ResidualBlock&&) = default;

	auto ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;

	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return receptiveField; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return (GetReceptiveField(size) - 1) / 2; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return stride; }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<ResidualBlock>(*this); }

private:
	const Matrix::Size receptiveField;
	const Matrix::Size stride;

	Layers layers;
};

}
