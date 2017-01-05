#pragma once
#include <vector>
#include <stdexcept>
#include "matrix.hpp"

namespace Convolutional {

class MultiMatrix {
public:
	struct Dimensionality {
		Matrix::Size size;
		std::size_t dimensionCount = 0;
	};

	using dimensions_t = std::vector<Matrix>;

    explicit MultiMatrix(dimensions_t subDimensions);
	MultiMatrix(const MultiMatrix&) = default;
	MultiMatrix(MultiMatrix&&) = default;

	MultiMatrix& operator=(const MultiMatrix&) & = default;
	MultiMatrix& operator=(MultiMatrix&&) & = default;

	MultiMatrix& operator+= (const MultiMatrix& other);

	auto AddZeroPadding(Matrix::Size paddingAmount) -> void;
	auto GetDimensionCount() const noexcept { return dimenstionality.dimensionCount; }
	auto GetElementCount() const noexcept { return dimenstionality.size.height * dimenstionality.size.width; }
	auto GetSize() const noexcept { return dimenstionality.size; }

	auto begin() noexcept { return subDimensions.begin(); }
	auto begin() const noexcept { return subDimensions.begin(); }
	auto end() noexcept { return subDimensions.end(); }
	auto end() const noexcept { return subDimensions.end(); }

private:
	template<typename Lambda>
	auto GetMultidimensionalProperty(Lambda&& lambda) const {
		auto result = lambda(subDimensions.front());
		for (const auto& dimension : subDimensions) {
			if (result != lambda(static_cast<Matrix>(dimension)))
				throw std::logic_error("Property was not consistent between dimensions");
		}
		return result;
	}

private:
	dimensions_t subDimensions;
	Dimensionality dimenstionality;
};

inline auto operator+ (MultiMatrix lhs, const MultiMatrix& rhs) { return lhs += rhs; }

}
