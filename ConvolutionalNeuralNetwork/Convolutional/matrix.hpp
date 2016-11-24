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
		auto operator==(const Size& other) const { return width == other.width && height == other.height; }
		auto operator!=(const Size& other) const { return !operator==(other); }
		std::size_t width = 0;
		std::size_t height = 0;
	};

public:
	explicit Matrix(Size size);

	auto GetSubmatrix(Position position, Size size) const -> Matrix;
	auto GetElementAt(Position position) const -> const elementType&;
	auto GetElementAt(Position position) -> elementType&;

	auto GetSize() const noexcept { return size; }
	auto GetElementCount() const noexcept { return GetSize().height * GetSize().width; }
	
	auto begin() noexcept { return elements.begin(); }
	auto begin() const noexcept { return elements.begin(); }
	auto end() noexcept { return elements.end(); }
	auto end() const noexcept { return elements.end(); }

private:
	const Size size;
	std::vector<elementType> elements;
};

}
