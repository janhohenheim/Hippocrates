#include "matrix.h"
using namespace Convolutional;


Matrix::Matrix(Size size):
	size(size)
{
	elements.reserve(GetElementCount());
}

/*
Matrix& Convolutional::Matrix::operator=(const Matrix & other)
{
	const_cast<size_t&>(width) = other.width;
	const_cast<size_t&>(height) = other.height;
	elements = other.elements;
	return *this;
}
*/

auto Matrix::GetSubmatrix(Matrix::Position position, Matrix::Size size) -> Matrix
{
	return Matrix(GetSize());
}
