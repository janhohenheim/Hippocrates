#include "multi_matrix.hpp"

using namespace Convolutional;

MultiMatrix::MultiMatrix(dimensions_t subDimensions) :
subDimensions(std::move(subDimensions))
{
}

auto MultiMatrix::AddZeroPadding(Matrix::Size paddingAmount) -> void {
	for (auto & matrix : subDimensions) {
		matrix.AddZeroPadding(paddingAmount);
	}
}

auto MultiMatrix::GetElementCount() const -> std::size_t {
	return GetMultidimensionalProperty([](const Matrix& m) {return m.GetElementCount(); });
}

auto MultiMatrix::GetSize() const -> Matrix::Size {
	return GetMultidimensionalProperty([](const Matrix& m) {return m.GetSize(); });
}
