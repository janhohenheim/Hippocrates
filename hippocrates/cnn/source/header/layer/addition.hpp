#pragma once

#include "layer/ilayer.hpp"
#include "layer/convolution.hpp"
#include "fillable_ref.hpp"

#include <optional>

namespace Convolutional::Layer {

class Addition : public ILayer {
public:
	using ILayer::ILayer;

	Addition(Hippocrates::Utility::FillableRef<MultiMatrix> summand, Matrix::Size stride) : summand {std::move(summand)}, stride {std::move(stride)}{};

	auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix override;
	auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;

	auto Clone() const -> std::unique_ptr<ILayer> override { return std::make_unique<Addition>(*this); }


	auto HasProjection() const -> bool {return projection.has_value(); }

private:
	Hippocrates::Utility::FillableRef<MultiMatrix> summand;

	auto GetBiggerDimensionality(const MultiMatrix::Dimensionality& lhs, const MultiMatrix::Dimensionality& rhs) const -> const MultiMatrix::Dimensionality&;
	auto GetSmallerDimensionality(const MultiMatrix::Dimensionality& lhs, const MultiMatrix::Dimensionality& rhs) const -> const MultiMatrix::Dimensionality&;
	auto GetBiggerMultiMatrix(const MultiMatrix& lhs, const MultiMatrix& rhs) const -> const MultiMatrix&;
	auto GetSmallerMultiMatrix(const MultiMatrix& lhs, const MultiMatrix& rhs) const -> const MultiMatrix&;

	std::optional<Convolution> projection;
	Matrix::Size stride;
};

}
