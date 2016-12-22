#include <cmath>
#include <stdexcept>
#include <vector>

#include "layer/filter.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;


auto Filter::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	const auto origSize = multiMatrix.GetSize();
	LazyInitializeWeights(origSize, multiMatrix.GetDimensionCount());

	auto paddedMM = multiMatrix;
	const auto padding = GetZeroPadding(origSize);
	paddedMM.AddZeroPadding(padding);

	const auto paddedSize = paddedMM.GetSize();
	const auto receptiveSize = GetReceptiveField(paddedSize);
	const auto stride = GetStride(paddedSize);
	Matrix::Size filteredSize;
	// If we set the the zero padding accordingly, these will be equal to origSize
	filteredSize.height = static_cast<std::size_t>(static_cast<double>(origSize.height - receptiveSize.height + 2 * padding.height) / static_cast<double>(stride.height) + 1.0);
	filteredSize.width = static_cast<std::size_t>(double(origSize.width - receptiveSize.width + 2 * padding.width) / static_cast<double>(stride.width) + 1.0);
	
	Matrix filteredMatrix {filteredSize};
	auto currFilteredElement = filteredMatrix.begin();
	Matrix::Position pos;
	for (pos.y = 0; pos.y < paddedSize.height - receptiveSize.height; pos.y += stride.height) {
		for (pos.x = 0; pos.x < paddedSize.width - receptiveSize.width; pos.x += stride.width) {
			Matrix::element_t filteredElement = 0;
			for (std::size_t dim = 0; dim < weights->GetDimensionCount(); ++dim) {
				const auto weightSize = weights->GetSize();
				const auto featureMap = (paddedMM.begin() + dim)->GetSubmatrix(pos, receptiveSize);
				const auto subWeights = *(weights->begin() + dim);
				for (std::size_t y = 0; y < weightSize.height; ++y) {
					for (std::size_t x = 0; x < weightSize.width; ++x) {
						filteredElement += featureMap.ElementAt({x, y}) * subWeights.ElementAt({x, y});
					}
				}
			}
			*(currFilteredElement++) = filteredElement + bias;
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
			element = Hippocrates::Utility::Random::Number(-1.0, 1.0);
		}
		matrices.push_back(std::move(matrix));
	}
	weights = std::make_unique<MultiMatrix>(std::move(matrices));
}

auto Filter::sigmoid(Matrix::element_t n) -> double {
	return tanh(n);
}

