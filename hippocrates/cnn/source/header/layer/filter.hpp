#pragma once
#include "matrix.hpp"
#include "ilayer.hpp"
#include "random.hpp"
#include <memory>

namespace Convolutional::Layer {

class Filter : public ILayer {
public:
	using ILayer::ILayer;

	explicit Filter(Matrix::Size receptiveField = {3, 3},
		Matrix::Size stride = {1, 1})
		: receptiveField(receptiveField),
		stride(stride),
		bias {Hippocrates::Utility::Random::Number(-1.0, 1.0)}
	{}
	Filter(const Filter& other) :
		receptiveField {other.receptiveField},
		stride {other.stride}, 
		bias {other.bias}
	{
		if (other.weights) 
			weights = std::make_unique<MultiMatrix>(*other.weights);
	};

	Filter(Filter&&) = default;

	auto ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;

	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return receptiveField; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return (GetReceptiveField(size) - 1) / 2; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return stride; }

	auto GetBias() const noexcept { return bias; }
	auto SetBias(double bias) noexcept { this->bias = bias; }
	auto GetWeights() const -> const MultiMatrix&;
	auto SetWeights(MultiMatrix weights) noexcept { this->weights.release(); this->weights = std::make_unique<MultiMatrix>(std::move(weights)); }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<Filter>(*this); }

private:
	auto LazyInitializeWeights(Matrix::Size size, std::size_t dimensionCount) -> void;

	const Matrix::Size receptiveField;
	const Matrix::Size stride;
	Matrix::element_t bias = 0;

	std::unique_ptr<MultiMatrix> weights;

};

}
