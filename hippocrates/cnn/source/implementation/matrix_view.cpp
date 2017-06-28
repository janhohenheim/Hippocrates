#include "matrix_view.hpp"
#include "matrix.hpp"

using namespace Convolutional;

MatrixView::MatrixView(const Matrix& parent, Position position, Size size)
: parent{parent},
  position{std::move(position)},
  size{std::move(size)},
  beginPosition{this->position.y * parent.GetSize().width + this->position.x}
{
}

MatrixView::MatrixView(const Matrix & parent) 
: MatrixView {parent, Position{0, 0}, parent.GetSize()}
{
}

auto MatrixView::GetSubmatrix(Position position, Size size) const -> MatrixView {
	return MatrixView(parent, position + this->position, size);
}

auto MatrixView::ElementAt(Position position) const -> const element_t& {
	return ElementAt(position.y * GetSize().width + position.x);
}

// TODO jnf: Implement everything under this comment

auto MatrixView::ElementAt(std::size_t position) const -> const element_t & {
	return parent.ElementAt(beginPosition + position / size.width * parent.GetSize().width + position % size.width);
}
