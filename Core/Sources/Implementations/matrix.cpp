#include "matrix.hpp"

using namespace Convolutional;

Matrix::Matrix(Size size):
	size(size),
	elements(size.height * size.width)
{
}

Convolutional::Matrix::Matrix(Size size, element_t value) :
	size(size),
	elements(size.height * size.width, value)
{
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

auto Convolutional::Matrix::AddZeroPadding(Matrix::Size paddingAmount) -> void {
	if (paddingAmount.height == 0 
	 && paddingAmount.width == 0)
		return;

	auto paddedSize = size;
	paddedSize.height += paddingAmount.height * 2;
	paddedSize.width += paddingAmount.width * 2;
	Matrix paddedMatrix(paddedSize);

	auto element = elements.begin();

	for (auto y = paddingAmount.height; y < paddedSize.height - paddingAmount.height; ++y)
		for (auto x = paddingAmount.width; x < paddedSize.width - paddingAmount.width; ++x)
			paddedMatrix.ElementAt({x, y}) = *(element++);
	
	*this = std::move(paddedMatrix);
}

auto Matrix::GetSubmatrix(Matrix::Position position, Matrix::Size size) const -> Matrix {
	Matrix subMatrix {size};
	Position subPos;
	for (; subPos.y < size.width; ++subPos.y) {
		for (; subPos.x < size.height; ++subPos.x) {
			Position macroPos = position;
			macroPos.x += subPos.x;
			macroPos.y += subPos.y;
			subMatrix.ElementAt(subPos) = ElementAt(macroPos);
		}
	}
	return subMatrix;
}

auto Matrix::ElementAt(Position position) const -> const element_t& {
	return const_cast<Matrix*>(this)->ElementAt(position);;
}

auto Matrix::ElementAt(Position position) -> element_t& {
	return elements[position.x * GetSize().width + position.y];
}
