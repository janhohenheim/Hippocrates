#include "multi_matrix.hpp"

using namespace Convolutional;

MultiMatrix::MultiMatrix(SubDimensionType subDimensions) :
subDimensions(std::move(subDimensions))
{
}

auto MultiMatrix::GetElementCount() const -> std::size_t {
	return GetMultidimensionalProperty([](const Matrix& m) {return m.GetElementCount(); });
}

auto MultiMatrix::GetSize() const -> Matrix::Size {
	return GetMultidimensionalProperty([](const Matrix& m) {return m.GetSize(); });
}
