#pragma once
#include <vector>
#include <cmath>

namespace Convolutional {

class Matrix {
public:
	using element_t = double;
	using elements_t = std::vector<element_t>;
	struct Position {
		std::size_t x = 0;
		std::size_t y = 0;
	};
	struct Size {
		auto operator==(const Size& other) const { return width == other.width && height == other.height; }
		auto operator!=(const Size& other) const { return !operator==(other); }
		template<typename T>
		auto operator+(T amount) { 
			width += static_cast<std::size_t>(amount);
			height += static_cast<std::size_t>(amount); 
			return *this;
		}
		template<typename T>
		auto operator-(T amount) {
			width -= static_cast<std::size_t>(amount);
			height -= static_cast<std::size_t>(amount);
			return *this;
		}
		template<typename T>
		auto operator/(T amount) {
			width = std::round(static_cast<T>(width) / amount);
			height = std::round(static_cast<T>(height) / amount);
			return *this;
		}

		std::size_t width = 0;
		std::size_t height = 0;
	};

public:
	explicit Matrix(Size size);
	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;

	auto GetSubmatrix(Position position, Size size) const -> Matrix;
	auto ElementAt(Position position) const -> const element_t&;
	auto ElementAt(Position position) -> element_t&;

	auto GetSize() const noexcept { return size; }
	auto GetElementCount() const noexcept { return GetSize().height * GetSize().width; }
	
	auto begin() noexcept { return elements.begin(); }
	auto begin() const noexcept { return elements.begin(); }
	auto end() noexcept { return elements.end(); }
	auto end() const noexcept { return elements.end(); }

private:
	const Size size;
	std::vector<element_t> elements;
};

}
