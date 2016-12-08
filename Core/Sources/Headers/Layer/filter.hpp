#pragma once
#include "matrix.hpp"
#include "ilayer.hpp"
#include "Utility/utility.hpp"
#include <memory>

namespace Convolutional::Layer {

class Filter : public ILayer {
public:
	using ILayer::ILayer;

	Filter(Matrix::Size receptiveField = {3, 3},
		Matrix::Size stride = {1, 1})
		: receptiveField(receptiveField),
		stride(stride),
		bias {Utility::GetRandomNumberBetween(-1.0, 1.0)}
	{}
	Filter(const Filter& other) :
		receptiveField {other.receptiveField},
		stride {other.stride}, 
		bias {other.bias},
		weights{ std::make_unique<MultiMatrix>(*weights) }
	{};
	Filter(Filter&&) = default;

	auto ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix override;

	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return receptiveField; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return GetReceptiveField(size) - 1 / 2; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return stride; }

	auto GetBias() const noexcept { return bias; }
	auto SetBias(double bias) noexcept { this->bias = bias; }
	auto GetWeights() const -> const MultiMatrix&;
	auto SetWeights(MultiMatrix weights) noexcept { this->weights.release(); this->weights = std::make_unique<MultiMatrix>(std::move(weights)); }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> { return std::make_unique<Filter>(*this); }

private:
	auto LazyInitializeWeights(Matrix::Size size, std::size_t dimensionCount) -> void;

	static auto sigmoid(Matrix::element_t n) -> double;

	const Matrix::Size receptiveField;
	const Matrix::Size stride;
	double bias = 0;

	std::unique_ptr<MultiMatrix> weights = nullptr;

};

}
