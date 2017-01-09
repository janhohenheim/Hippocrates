#include "matrix.hpp"
#include <stdexcept>

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

Matrix& Matrix::operator+=(const Matrix & other) {
	if (GetElementCount() != other.GetElementCount())
		throw std::logic_error {"Tried to add two Matrices with different sizes"};

	for (std::size_t i = 0; i < GetElementCount(); ++i) {
		ElementAt(i) += other.ElementAt(i);
	}
	return *this;
}

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
	if (size == GetSize())
		return *this;

	Matrix subMatrix {size};
	Position subPos;
	for (subPos.y = 0; subPos.y < size.width; ++subPos.y) {
		for (subPos.x = 0; subPos.x < size.height; ++subPos.x) {
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
	return elements[position.y * GetSize().width + position.x];
}

auto Convolutional::Matrix::ElementAt(std::size_t position) const -> const element_t & {
	return const_cast<Matrix*>(this)->ElementAt(position);;
}

auto Convolutional::Matrix::ElementAt(std::size_t position) -> element_t & {
	return *(this->begin() + position);
}
