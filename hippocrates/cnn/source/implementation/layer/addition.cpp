#include "layer/addition.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto Addition::ProcessMultiMatrix(const MultiMatrix & multiMatrix) -> MultiMatrix {
	const auto & smaller = GetSmallerMultiMatrix(*summand, multiMatrix);
	const auto & bigger = GetBiggerMultiMatrix(*summand, multiMatrix);
	
	if (&smaller == &bigger)
		return smaller + bigger;

	auto scaledSmaller = smaller;

	auto const smallDim = smaller.GetDimensionality();
	auto const bigDim = smaller.GetDimensionality();

	if (smallDim.dimensionCount != bigDim.dimensionCount) {
		if (!projection.has_value()) {
			Filter f {{1, 1}, stride};
			projection = std::make_optional<Convolution>(bigDim.dimensionCount, std::move(f));
		}
		scaledSmaller = projection->ProcessMultiMatrix(smaller);
	}

	auto const smallElemCount = smallDim.size.width * smallDim.size.height;
	auto const bigElemCount = bigDim.size.width * bigDim.size.height;

	if (smallElemCount < bigElemCount) {
		// TODO jnf: implement
	}

	return scaledSmaller;
}

auto Addition::GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality {
	return GetBiggerDimensionality(summand->GetDimensionality(), dimensionality);
}

auto Addition::GetBiggerDimensionality(const MultiMatrix::Dimensionality& lhs, const MultiMatrix::Dimensionality& rhs) const -> const MultiMatrix::Dimensionality & {
	auto const lhsElemCount = lhs.size.width * lhs.size.height;
	auto const rhsElemCount = rhs.size.width * rhs.size.height;
	if (lhs.dimensionCount < rhs.dimensionCount || lhsElemCount < rhsElemCount)
		return rhs;

	return lhs;
}

auto Addition::GetSmallerDimensionality(const MultiMatrix::Dimensionality & lhs, const MultiMatrix::Dimensionality & rhs) const -> const MultiMatrix::Dimensionality & {
	if (&GetBiggerDimensionality(lhs, rhs) == &lhs)
		return rhs;
	return lhs;
}

auto Addition::GetBiggerMultiMatrix(const MultiMatrix & lhs, const MultiMatrix & rhs) const -> const MultiMatrix & {
	if (&GetBiggerDimensionality(lhs.GetDimensionality(), rhs.GetDimensionality()) == &rhs.GetDimensionality())
		return rhs;
	return lhs;
}

auto Addition::GetSmallerMultiMatrix(const MultiMatrix & lhs, const MultiMatrix & rhs) const -> const MultiMatrix & {
	if (&GetBiggerMultiMatrix(lhs, rhs) == &lhs)
		return rhs;
	return lhs;
}
