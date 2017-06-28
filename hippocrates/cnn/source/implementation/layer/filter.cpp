#include <cmath>
#include <stdexcept>
#include <vector>
#include <thread>
#include <numeric>

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
			const auto filteredElement = AccumulateProduct(paddedMM, *weights, pos, receptiveField);			
			*(currFilteredElement++) = filteredElement + bias;
		}
	}
	return MultiMatrix {{filteredMatrix}};
}

auto Filter::AccumulateProduct(
	const MultiMatrix& mm, 
	const MultiMatrix& weights, 
	Matrix::Position pos, 
	Matrix::Size size
	) -> Matrix::element_t {
	Matrix::element_t filteredElement = 0;

	const std::size_t length = weights.GetDimensionCount();
	const std::size_t min_per_thread = 1;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;
	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();
	const std::size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	const std::size_t block_size = length / num_threads;
	std::vector<Matrix::element_t> results(num_threads);
	std::vector<std::thread> threads(num_threads - 1);
	std::size_t block_start = 0;
	for (std::size_t i = 0; i<(num_threads - 1); ++i) {
		auto block_end = block_start;
		block_end += block_size;
		threads[i] = std::thread(
			AccumulateProductBlock,
			std::ref(mm),
			std::ref(weights),
			block_start, 
			block_end,
			pos,
			size,
			std::ref(results[i]));
		block_start = block_end;
	}
	AccumulateProductBlock(
		std::ref(mm),
		std::ref(weights),
		block_start, 
		length,
		pos,
		size,
		std::ref(results[num_threads - 1]));
	std::for_each(threads.begin(), threads.end(),
			std::mem_fn(&std::thread::join));
	return std::accumulate(results.begin(), results.end(), Matrix::element_t(0));
}

auto Filter::AccumulateProductBlock(
	const MultiMatrix& mm,
	const MultiMatrix& weights,
	std::size_t start_block,
	std::size_t end_block,
	Matrix::Position pos,
	Matrix::Size size,
	Matrix::element_t& result
	) -> void {
	for (std::size_t dim = start_block; dim < end_block; ++dim) {
		const auto featureMap = (mm.begin() + dim)->GetSubmatrix(pos, size);
		const auto& subWeights = *(weights.begin() + dim);
		for (std::size_t i = 0; i < featureMap.GetElementCount(); ++i) {
			result += featureMap.ElementAt(i) * subWeights.ElementAt(i);
		}
	}
}

auto Filter::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	const auto size = dimensionality.size;
	const auto r = GetReceptiveField(size);
	const auto s = GetStride(size);
	const auto p = GetZeroPadding(size);

	MultiMatrix::Dimensionality newDim;
	newDim.size.height = (size.width - r.width + 2 * p.width) / s.width + 1;
	newDim.size.width = (size.height - r.height + 2 * p.height) / s.height + 1;
	newDim.dimensionCount = dimensionality.dimensionCount;
	return newDim;
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
