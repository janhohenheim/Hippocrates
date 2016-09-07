#pragma once
#include "multi_dimensional_matrix.h"

namespace Convolutional {

class MultiDimensionalMatrixParser {
public:
    using Image = std::nullptr_t;
    using Sentence = std::string;

    static auto Parse(const Image& image) -> MultiDimensionalMatrix;
    static auto Parse(const Sentence& sentence) -> MultiDimensionalMatrix;
};

}