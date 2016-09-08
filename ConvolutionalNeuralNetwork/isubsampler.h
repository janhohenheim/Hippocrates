#pragma once
#include "multi_matrix.h"

namespace Convolutional {
namespace SubSampler {

class ISubSampler {
public:
    virtual auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) const ->MultiMatrix final;

    virtual auto ProcessMatrix(Matrix::Position position, const Matrix& net) const -> Matrix = 0;
    virtual auto GetReceptiveField() const -> Matrix::Size = 0;
    virtual auto GetZeroPadding() const -> Matrix::Size = 0;
};

}
}
