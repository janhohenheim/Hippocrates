#include "multi_matrix.hpp"
#include <stdexcept>

using namespace Convolutional;

MultiMatrix::MultiMatrix(dimensions_t subDimensions) :
subDimensions(std::move(subDimensions))
{
}

MultiMatrix& Convolutional::MultiMatrix::operator+=(const MultiMatrix & other) {
	if (GetDimensionCount() != other.GetDimensionCount())
		throw std::logic_error{"Tried to add two MultiMatrices with different dimensionalities"};

	for (std::size_t i = 0; i < GetDimensionCount(); ++i) {
		subDimensions[i] += other.subDimensions[i];
	}
	return *this;
}

auto MultiMatrix::AddZeroPadding(Matrix::Size paddingAmount) -> void {
	for (auto & matrix : subDimensions) 
		matrix.AddZeroPadding(paddingAmount);
}

auto MultiMatrix::GetElementCount() const -> std::size_t {
	return GetMultidimensionalProperty([](const Matrix& m) {return m.GetElementCount(); });
}

auto MultiMatrix::GetSize() const -> Matrix::Size {
	return GetMultidimensionalProperty([](const Matrix& m) {return m.GetSize(); });
}
