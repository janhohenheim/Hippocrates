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
        for (; pos.y < size.height; pos.y += receptiveField.height) {
            for (; pos.x < size.width; pos.x += receptiveField.width) {
                auto processedMatrix = ProcessMatrix(pos, submatrix);
                dimensions.push_back(std::move(processedMatrix));
            }
        }
    }
    return MultiMatrix(dimensions);
}
