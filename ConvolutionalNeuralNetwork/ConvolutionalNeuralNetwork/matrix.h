#pragma once
#include <vector>

namespace Convolutional {

class Matrix {
public:
	using elementType = std::size_t;

	Matrix(std::size_t width, std::size_t height);
	/*
	Matrix(const Matrix& other) = default;
	Matrix(Matrix&& other) = default;
	auto operator= (const Matrix& other) -> Matrix&;
	auto operator= (Matrix&& other) -> Matrix& = default;
	*/

	auto GetSubmatrix(std::size_t width, std::size_t height) -> Matrix;

	auto GetHeight() const { return width; }
	auto GetWidth() const { return height; }
	auto GetSize() const { return GetHeight() * GetWidth(); }

private:
	const std::size_t width = 0;
	const std::size_t height = 0;
	std::vector<elementType> elements;
};

}