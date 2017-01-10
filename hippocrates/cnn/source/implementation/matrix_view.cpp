#include "matrix_view.hpp"
#include "matrix.hpp"

using namespace Convolutional;

MatrixView::MatrixView(const Matrix & parent) 
: MatrixView {parent, {0, 0}, parent.GetSize()}
{
}

auto MatrixView::GetSubmatrix(Position position, Size size) const -> MatrixView {
	return MatrixView(parent, position, size);
}

auto MatrixView::ElementAt(Position position) const -> const element_t& {
	return ElementAt(position.y * GetSize().width + position.x);
}

// TODO jnf: Implement everything under this comment

auto MatrixView::ElementAt(std::size_t position) const -> const element_t & {
	return parent.ElementAt(position);
}

auto MatrixView::begin() const noexcept -> std::vector<double>::const_iterator {
	return parent.begin();
}

auto MatrixView::end() const noexcept -> std::vector<double>::const_iterator {
	return parent.end();
}
