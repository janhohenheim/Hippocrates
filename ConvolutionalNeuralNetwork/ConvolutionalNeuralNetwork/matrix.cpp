#include "matrix.h"
using namespace Convolutional;


Convolutional::Matrix::Matrix(std::size_t width, std::size_t height):
	width(width),
	height(height)
{
	elements.reserve(GetSize());
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

auto Matrix::GetSubmatrix(std::size_t width, std::size_t height) -> Matrix
{
	return Matrix(width, height);
}
