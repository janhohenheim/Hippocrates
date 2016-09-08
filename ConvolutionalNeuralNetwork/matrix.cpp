#include "matrix.h"
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

auto Matrix::GetSubmatrix(Matrix::Position position, Matrix::Size size) const -> Matrix
{
    Matrix subMatrix {size};
    Position subPos;
    for (; subPos.y < size.width; ++subPos.y) {
        for (; subPos.x < size.height; ++subPos.x) {
            Position macroPos = position;
            macroPos.x += subPos.x;
            macroPos.y += subPos.y;
            subMatrix.GetElementAt(subPos) = GetElementAt(macroPos);
        }
    }
	return subMatrix;
}

auto Convolutional::Matrix::GetElementAt(Position position) const -> elementType
{
    return GetElementAt(position);
}

auto Convolutional::Matrix::GetElementAt(Position position) -> elementType&
{
	return elements[position.x * GetSize().width + position.y];
}
