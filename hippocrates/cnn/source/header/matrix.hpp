#pragma once
#include <vector>
#include <cmath>
#include "matrix_view.hpp"

namespace Convolutional {

class Matrix {
public:
	using element_t = MatrixView::element_t;
	using elements_t = std::vector<element_t>;
	using Size = MatrixView::Size;
	using Position = MatrixView::Position;

public:
	explicit Matrix(Size size);
	explicit Matrix(Size size, element_t value);
	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;

	Matrix& operator= (const Matrix&) = default;
	Matrix& operator= (Matrix&&) = default;

	Matrix& operator+= (const Matrix& other);

	auto AddZeroPadding(Matrix::Size paddingAmount) -> void;
	auto GetSubmatrix(Position position, Size size) const -> MatrixView;
	auto ElementAt(Position position) const -> const element_t&;
	auto ElementAt(Position position) -> element_t&;
	auto ElementAt(std::size_t position) const -> const element_t&;
	auto ElementAt(std::size_t position) -> element_t&;

	auto GetSize() const noexcept { return size; }
	auto GetElementCount() const noexcept { return GetSize().height * GetSize().width; }
	
	auto begin() noexcept { return elements.begin(); }
	auto begin() const noexcept { return elements.begin(); }
	auto end() noexcept { return elements.end(); }
	auto end() const noexcept { return elements.end(); }

private:
	Size size;
	elements_t elements;
};

inline auto operator+ (Matrix lhs, const Matrix& rhs) { return lhs += rhs; }


}
