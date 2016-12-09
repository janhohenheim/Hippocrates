#include "matrix.hpp"

using namespace Convolutional;

Matrix::Matrix(Size size):
	size(size),
	elements(size.height * size.width)
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
	// Pad left and right
	for (auto element = elements.begin(); element != elements.end(); ++element) {
		elements.insert(element, 0);
		element+=size.width;
		elements.insert(element, 0);
	}
	elements.push_back(0);

	size.height += paddingAmount.height * 2;
	size.width += paddingAmount.width * 2;

	// Pad above and below
	for (std::size_t i = 0; i < paddingAmount.height * size.width; ++i) {
		elements.push_front(0);
		elements.push_back(0);
	}
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
