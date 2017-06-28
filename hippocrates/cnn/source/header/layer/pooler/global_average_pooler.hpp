#pragma once
#include "layer/pooler/ipooler.hpp"

namespace Convolutional::Layer::Pooler {

	class GlobalAveragePooler : public IPooler {
	public:
		using IPooler::IPooler;

		auto ProcessMultiMatrix(const MultiMatrix& multiMatrix)->MultiMatrix override;
		auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override;

		auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<GlobalAveragePooler>(*this); }


		auto ProcessMatrix(const Matrix& matrix) const -> Matrix::element_t;
	};

}
