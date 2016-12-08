#pragma once
#include "matrix.hpp"
#include "ilayer.hpp"
#include <vector>

namespace Convolutional::Layer {

class Filter : public ILayer {
public:
	Filter(std::size_t size);
	Filter(double bias, std::vector<double>&& weights) : bias(bias), weights(std::move(weights)) {}

	auto ProcessMatrix(Matrix matrix) const -> Matrix override;
	auto GetReceptiveField(Matrix::Size size) const noexcept -> Matrix::Size override { return {3, 3}; }
	auto GetZeroPadding(Matrix::Size size) const noexcept -> Matrix::Size override { return GetReceptiveField(size) - 1 / 2; }
	auto GetStride(Matrix::Size size) const noexcept -> Matrix::Size override { return {1, 1}; }

	auto GetBias() const noexcept { return bias; }
	auto GetWeights() const noexcept { return weights; }

	auto Clone() const noexcept -> std::unique_ptr<ILayer> { return std::make_unique<Filter>(*this); }

public:
	std::vector<double> weights;
	double bias = 0;

private:
	static auto sigmoid(Matrix::element_t n) -> double;
};

}
