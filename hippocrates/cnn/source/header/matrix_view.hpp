#pragma once
#include <cstddef>
#include <vector>

namespace Convolutional {

class Matrix;

class MatrixView {
public:
	using element_t = double;

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
			width = static_cast<std::size_t>(std::round(static_cast<T>(width) / amount));
			height = static_cast<std::size_t>(std::round(static_cast<T>(height) / amount));
			return *this;
		}

		std::size_t width = 0;
		std::size_t height = 0;
	};


	MatrixView(const Matrix& parent, Position position, Size size) : parent {parent} { }
	MatrixView(const Matrix& parent) : parent {parent} { }

	auto GetSubmatrix(Position position, Size size) const -> MatrixView;
	auto ElementAt(Position position) const -> const element_t&;
	auto ElementAt(std::size_t position) const -> const element_t&;

	auto GetSize() const noexcept { return size; }
	auto GetElementCount() const noexcept { return GetSize().height * GetSize().width; }

	auto begin() const noexcept -> std::vector<double>::const_iterator;
	auto end() const noexcept -> std::vector<double>::const_iterator;

private:
	const Matrix& parent;
	Position position;
	Size size;
};

}
