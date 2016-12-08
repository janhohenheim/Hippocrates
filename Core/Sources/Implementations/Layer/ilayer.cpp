#include "Layer/ilayer.hpp"

using namespace Convolutional;
using namespace Convolutional::Layer;

auto ILayer::ProcessMultiMatrix(const MultiMatrix & multiMatrix) const -> MultiMatrix {
    MultiMatrix::dimensions_t dimensions;
    dimensions.reserve(multiMatrix.GetDimensionCount());
    for (auto& submatrix : multiMatrix) {
        Matrix::Position pos;
		const auto size = submatrix.GetSize();
		const auto receptiveField = GetReceptiveField(size);
		const auto stride = GetStride(size);
        for (; pos.y < size.height; pos.y += stride.height) {
            for (; pos.x < size.width; pos.x += stride.width) {
				auto receptedMatrix = submatrix.GetSubmatrix(pos, receptiveField);
                dimensions.push_back(ProcessMatrix(std::move(receptedMatrix)));
            }
        }
    }
    return MultiMatrix(dimensions);
}
