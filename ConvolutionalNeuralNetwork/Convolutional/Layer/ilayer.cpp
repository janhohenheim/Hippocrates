#include "ilayer.hpp"
using namespace Convolutional;
using namespace Layer;

auto ILayer::ProcessMultiMatrix(const MultiMatrix & multiMatrix) const -> MultiMatrix {
    MultiMatrix::SubDimensionType dimensions;
    dimensions.reserve(multiMatrix.GetDimensionCount());
    for (auto& submatrix : multiMatrix) {
        Matrix::Position pos;
        for (; pos.y < submatrix.GetSize().height; pos.y += GetReceptiveField().height) {
            for (; pos.x < submatrix.GetSize().width; pos.x += GetReceptiveField().width) {
                auto processedMatrix = ProcessMatrix(pos, submatrix);
                dimensions.push_back(std::move(processedMatrix));
            }
        }
    }
    return MultiMatrix(dimensions);
}
