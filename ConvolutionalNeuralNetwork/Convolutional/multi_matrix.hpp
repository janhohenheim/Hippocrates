#pragma once
#include <vector>
#include <memory>
#include "matrix.hpp"

namespace Convolutional {

class MultiMatrix {
public:
	using SubDimensionType = std::vector<Matrix>;

	MultiMatrix(SubDimensionType subDimensions);

	auto GetDimensionCount() const noexcept { return subDimensions.size(); }

	auto begin() noexcept { return subDimensions.begin(); }
	const auto begin() const noexcept { return subDimensions.begin(); }
	auto end() noexcept { return subDimensions.end(); }
	const auto end() const noexcept { return subDimensions.end(); }

private:
	SubDimensionType subDimensions;
};

}
