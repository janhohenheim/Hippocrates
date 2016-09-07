#pragma once
#include <vector>

namespace Convolutional {

class Matrix {
public:
	using elementType = std::size_t;
	struct Position {
		std::size_t x = 0;
		std::size_t y = 0;
	};
	struct Size {
		std::size_t width = 0;
		std::size_t height = 0;
	};

public:
	Matrix(Size size);
	/*
	Matrix(const Matrix& other) = default;
	Matrix(Matrix&& other) = default;
	auto operator= (const Matrix& other) -> Matrix&;
	auto operator= (Matrix&& other) -> Matrix& = default;
	*/
	auto GetSubmatrix(Position position, Size size) -> Matrix;

	auto GetSize() const { return size; }
	auto GetElementCount() const { return GetSize().height * GetSize().width; }

private:
	const Size size;
	std::vector<elementType> elements;
};

}
