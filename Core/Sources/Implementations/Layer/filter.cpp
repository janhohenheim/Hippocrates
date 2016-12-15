#include <cmath>
#include <stdexcept>
#include <vector>

#include "Layer/filter.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;


auto Filter::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	const auto origSize = multiMatrix.GetSize();
	LazyInitializeWeights(origSize, multiMatrix.GetDimensionCount());

	Matrix filteredMatrix {origSize};
	auto paddedMM = multiMatrix;
	paddedMM.AddZeroPadding(GetZeroPadding(origSize));

	const auto paddedSize = paddedMM.GetSize();
	const auto receptiveField = GetReceptiveField(paddedSize);
	const auto stride = GetStride(paddedSize);
	Matrix::Position pos;
	for (; pos.y < paddedSize.height - receptiveField.height; pos.y += stride.height) {
		for (; pos.x < paddedSize.width - receptiveField.width; pos.x += stride.width) {
			for (std::size_t dim = 0; dim < weights->GetDimensionCount(); ++dim) {
				const auto weightSize = weights->GetSize();
				const auto featureMap = (paddedMM.begin() + dim)->GetSubmatrix(pos, receptiveField);
				const auto subWeights = *(paddedMM.begin() + dim);
				for (std::size_t y = 0; y < weightSize.height; ++y) {
					for (std::size_t x = 0; x < weightSize.width; ++x) {
						filteredMatrix.ElementAt({x, y}) = featureMap.ElementAt({x, y}) * subWeights.ElementAt({x, y});
					}
				}
			}
		}
	}
	return MultiMatrix {{filteredMatrix}};
}

auto Filter::GetWeights() const -> const MultiMatrix& {
	if (!weights) 
		throw std::runtime_error("Weights have not been initialized yet! Call ProcessMultiMatrix first"); 
	return *weights;
}

auto Filter::LazyInitializeWeights(Matrix::Size size, std::size_t dimensionCount) -> void {
	if (weights) {
		return;
	}

	// TODO jnf: constexpr check if size is perfect square
	std::vector<Matrix> matrices;
	matrices.reserve(dimensionCount);
	for (std::size_t i = 0; i < dimensionCount; ++i) {
		Matrix matrix {GetReceptiveField(size)};
		for (auto& element : matrix) {
			element = Utility::GetRandomNumberBetween(-1.0, 1.0);
		}
		matrices.push_back(std::move(matrix));
	}
	weights = std::make_unique<MultiMatrix>(std::move(matrices));
}

auto Filter::sigmoid(Matrix::element_t n) -> double {
	return tanh(n);
}

